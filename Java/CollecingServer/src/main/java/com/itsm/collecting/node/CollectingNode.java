package com.itsm.collecting.node;

import com.itsm.collecting.util.StringUtil;
import org.apache.log4j.Logger;
import org.apache.zookeeper.*;
import org.apache.zookeeper.data.Stat;

import java.net.InetAddress;
import java.net.UnknownHostException;
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

    public CollectingNode(String masterNodeName, String slaveNodeName, INodeTask task) {
        this.masterNodeName = masterNodeName;
        this.task = task;
        this.slaveNodeName = slaveNodeName;
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
                    isLeader = true;
                    logger.info("I am  master node");
                    task.startMasterTask();
                    break;
                case NODEEXISTS:
                    isLeader = false;
                    logger.info("I am slave node");
                    task.startSlaveTask();
                    masterExists();
                default:
                    isLeader = false;
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
                    logger.info("Registered sucessfully " + getUid());
                    break;
                case NODEEXISTS:
                    logger.warn("Already registerd : " + getUid());
                    break;
                default:
                    logger.error("something wrong :" +   KeeperException.create(KeeperException.Code.get(i), s));

            }
        }
    };

    private AsyncCallback.StatCallback masterExistsCallback = new AsyncCallback.StatCallback() {
        @Override
        public void processResult(int i, String s, Object o, Stat stat) {
            switch (KeeperException.Code.get(i)) {
                case CONNECTIONLOSS:
                    // ReCheck
                    masterExists();
                    break;
                case OK:
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

    public void masterExists() {
        zk.exists(masterNodeName, masterExistsWatch, masterExistsCallback, null);
    }

    // Listen master node delete thing
    private Watcher masterExistsWatch = new Watcher() {
        @Override
        public void process(WatchedEvent watchedEvent) {
            if(watchedEvent.getType() == Event.EventType.NodeDeleted) {
                assert masterNodeName.equals(watchedEvent.getPath());
                runForMaster();
            }
        }
    };

    // Create zookeeper connection
    public void startZK() {
        try {
            String addr = ip + ":" + hostPort;
            zk = new ZooKeeper(addr, 15000, this);
        } catch (Exception e) {

        }
    }

    public boolean isLeaderMaster() {
        return isLeader;
    }

    public void createParent(String path, byte[] data) {
        zk.create(path, data, ZooDefs.Ids.OPEN_ACL_UNSAFE, CreateMode.PERSISTENT, createParentCallback, data);
    }

    // 创建其他的work
    public void bootstrap() {
        createParent(slaveNodeName, new byte[0]);
    }

    // 作为主节点中的管理接运行
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

    public void runNode() {
        if(isLeaderMaster()) {
            task.startMasterTask();
        } else {
            registerSlaveNode();
            task.startSlaveTask();
        }
    }

    public static  void main(String args[]) throws Exception {
        // 创建客户端
        CollectingNode c = new CollectingNode("/master", "/slavers", null);
        c.startZK();
        c.bootstrap();
        c.runForMaster();
        Thread.sleep(100000);
        c.stopZK();
    }

    public void registerSlaveNode() {
        String name = slaveNodeName + "/slaver-" + getUid();
        zk.create(name, "Idle".getBytes(), ZooDefs.Ids.OPEN_ACL_UNSAFE, CreateMode.EPHEMERAL, createSlaveCallback, null);
    }



    private String getUid() {
        return serverId + "-" + localHostName;
    }

}
