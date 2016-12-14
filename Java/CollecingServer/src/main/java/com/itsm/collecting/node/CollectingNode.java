package com.itsm.collecting.node;

import com.itsm.collecting.util.StringUtil;
import com.sun.glass.ui.EventLoop;
import org.apache.log4j.Logger;
import org.apache.zookeeper.*;
import org.apache.zookeeper.data.Stat;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import static org.apache.zookeeper.ZooDefs.Ids.OPEN_ACL_UNSAFE;

/**
 * Created by bruce on 16-11-21.
 */
public class CollectingNode implements Watcher {

    private ZooKeeper zk;
    private static final String hostPort = StringUtil.getZookeeperPort();
    private static final String ip =  StringUtil.getZookeeperIp();
    private boolean isLeader = false;
    private String serverId = Integer.toHexString(new Random().nextInt());


    private static Logger logger = Logger.getLogger(CollectingNode.class);
    private final String masterNodeName;
    private final String slaveNodeName;
    private final String rootSlaveName;

    private INodeTask task;
    private static  String localHostName ;

    static {
        try {
            InetAddress addr = InetAddress.getLocalHost();
            localHostName = addr.getHostName();
        } catch (UnknownHostException e) {
            logger.error(e);
        }
    }

    public CollectingNode(String masterNodeName, String rootSlaveNodeName, INodeTask task) {
        this.masterNodeName = masterNodeName;
        this.task = task;
        this.rootSlaveName  = rootSlaveNodeName;
        String name = rootSlaveNodeName + "/slaver-" + getUid();
        this.slaveNodeName = name;
    }

    // A callback to create a parent node
    private AsyncCallback.StringCallback  createParentCallback = new AsyncCallback.StringCallback() {
        public void processResult(int i, String s, Object o, String s1) {
             switch (KeeperException.Code.get(i)) {
                 case CONNECTIONLOSS:
                     createParent(s, (byte[])o);
                     break;
                 case OK:
                     break;
                 case NODEEXISTS:
                     logger.info("parent has been created before");
             }
        }
    };

    // A callback to create a master node
    private AsyncCallback.StringCallback createMasterNodeCallback = new AsyncCallback.StringCallback() {

        @Override
        public void processResult(int i, String s, Object o, String s1) {
            switch(KeeperException.Code.get(i)) {
                case CONNECTIONLOSS:
                    checkMaster();
                    return;
                case OK:
                    synchronized (task) {
                        task.notify();
                        isLeader = true;
                    }

                    logger.info("I am  master node " + getUid());
                    List<String> slaveNodes = getChildrenNodeName(rootSlaveName);
                    for(String node : slaveNodes) {
                        if(node.equals("slaver-" + getUid())) {
                            deregisterSlaveNode(slaveNodeName);
                        }
                    }
                    break;
                case NODEEXISTS:
                    synchronized (this) {
                        isLeader = false;
                    }
                    masterExists();
                    registerSlaveNode();
                    logger.info("I am slave node " + getUid());
                    break;
                default:
                    synchronized (this) {
                        isLeader = false;
                    }

            }
        }
    };

    // A callback to get master data callback
    private AsyncCallback.DataCallback masterCheckCallback = new AsyncCallback.DataCallback() {
        @Override
        public void processResult(int i, String s, Object o, byte[] bytes, Stat stat) {
            switch (KeeperException.Code.get(i)) {
                case CONNECTIONLOSS:
                    checkMaster();
                    return;
                case NONODE:
                    runForMaster();
                    return;
            }
        }

    };

    private AsyncCallback.StringCallback createSlaveCallback = new AsyncCallback.StringCallback() {
        public void processResult(int i, String s, Object o, String s1) {

            switch (KeeperException.Code.get(i)) {
                case CONNECTIONLOSS:
                    registerSlaveNode();
                    break;
                case OK:
                    logger.info("Registered successfully " + getUid());
                    break;
                case NODEEXISTS:
                    logger.warn("Already registered : " + getUid());
                    break;
                default:
                    logger.error("something wrong :" +   KeeperException.create(KeeperException.Code.get(i), s));

            }
        }
    };

    //
    private AsyncCallback.StatCallback masterExistsCallback = new AsyncCallback.StatCallback() {
        @Override
        public void processResult(int i, String s, Object o, Stat stat) {
            switch (KeeperException.Code.get(i)) {
                case CONNECTIONLOSS:
                    // ReCheck
                    masterExists();
                    break;
                case OK:
                    // If no node
                    if(stat == null) {
                        runForMaster();
                    }
                    break;
                default:
                    checkMaster();
                    break;
            }

        }
    };

    // Listen master node delete event and run as a master to
    private Watcher masterExistsWatch = new Watcher() {
        @Override
        public void process(WatchedEvent watchedEvent) {
            if(watchedEvent.getType() == Event.EventType.NodeDeleted) {
                assert masterNodeName.equals(watchedEvent.getPath());
                runForMaster();
            }
        }
    };

    public void masterExists() {
        zk.exists(masterNodeName, masterExistsWatch, masterExistsCallback, null);
    }


    // Create zookeeper connection
    public void startZK() {
        try {
            String addr = ip + ":" + hostPort;
            zk = new ZooKeeper(addr, 15000, this);
        } catch (Exception e) {

            logger.error(e);
        }
    }

    public  synchronized  boolean isLeaderMaster() {
        return isLeader;
    }

    public void createParent(String path, byte[] data) {
        zk.create(path, data, ZooDefs.Ids.OPEN_ACL_UNSAFE, CreateMode.PERSISTENT, createParentCallback, data);
    }

    // 创建其他的work
    public void bootstrap() {
        createParent(rootSlaveName, new byte[0]);
    }

    // As a master run
    public void runForMaster() {
        zk.create(masterNodeName, serverId.getBytes(), OPEN_ACL_UNSAFE,  CreateMode.EPHEMERAL, createMasterNodeCallback, null);
    }

    // Check whethe node is Master node
    private void checkMaster() {
        zk.getData(masterNodeName, false, masterCheckCallback, null);
    }

    public void process(WatchedEvent watchedEvent) {
        logger.info(watchedEvent);
    }

    public void stopZK() throws  Exception {
        zk.close();
    }


    public static  void main(String args[]) throws Exception {
        CollectingNode c = new CollectingNode("/master", "/slavers", null);
        c.startZK();
        c.bootstrap();
        c.runForMaster();
        Thread.sleep(100000);
        c.stopZK();
    }


    private void registerSlaveNode() {
        zk.create(slaveNodeName, "Idle".getBytes(), ZooDefs.Ids.OPEN_ACL_UNSAFE, CreateMode.EPHEMERAL, createSlaveCallback, null);
    }


    private void deregisterSlaveNode(String node) {
        try {
            zk.delete(node, -1);
            logger.info("delete slave node " + slaveNodeName + " successfully");
        } catch (Exception e) {
            logger.error(e);
        }
    }


    private String getUid() {
        return serverId + "-" + localHostName;
    }

    private List<String> getChildrenNodeName(String root) {
        try {
            Stat stat = new Stat();
            List<String> nodes = zk.getChildren(root, false, stat);
            return nodes;
        } catch (KeeperException e) {
            return new ArrayList<String>();
        } catch(InterruptedException e) {
            return new ArrayList<String>();
        }
    }

}
