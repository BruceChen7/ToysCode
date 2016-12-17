package com.itsm.collecting.node;

import com.itsm.collecting.util.StringUtil;
import org.apache.log4j.Logger;
import org.apache.zookeeper.*;
import org.apache.zookeeper.data.Stat;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import static org.apache.zookeeper.ZooDefs.Ids.OPEN_ACL_UNSAFE;

/**
 * Created by bruce on 16-11-21.
 */
public class PullCollectingNode implements Watcher {

    private ZooKeeper zk;
    private static final String hostPort = StringUtil.getZookeeperPort();
    private static final String ip =  StringUtil.getZookeeperIp();
    private boolean isLeader = false;

    private static Logger logger = Logger.getLogger(PullCollectingNode.class);
    // For example: /master
    private final String masterNodeName;
    // e.g: slaver-1
    private String path;
    // e.g: /slavers
    private final String rootSlaveName;
    private final String slavePrefix =  "/slave-";

    private RabbitMQNodeTask task;
    private static  String localHostName ;


    static {
        try {
            InetAddress addr = InetAddress.getLocalHost();
            localHostName = addr.getHostName();
        } catch (UnknownHostException e) {
            logger.error(e);
        }
    }

    public PullCollectingNode(String masterNodeName, String rootSlaveNodeName, RabbitMQNodeTask task) {
        this.masterNodeName = masterNodeName;
        this.task = task;
        this.rootSlaveName  = rootSlaveNodeName;
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
            List<String>  slaveNodes = getChildrenNodeName(rootSlaveName);
            logger.info("slave node size is " + slaveNodes.size());
            // avoid null
            slaveNodes = slaveNodes == null ? new ArrayList<String>(): slaveNodes;

            switch(KeeperException.Code.get(i)) {
                case CONNECTIONLOSS:
                    checkMaster();
                    return;
                case OK:
                    synchronized (task) {
                        // notify the task can be started
                        task.notify();
                        isLeader = true;
                    }

                    logger.info("original path is " + path);

                    boolean isInSlave = false;
                    if(path != null) {
                        isInSlave = slaveNodes.contains(path.substring(path.lastIndexOf('/') + 1));
                    }

                    if(isInSlave) {
                        logger.info("begin to deregister node " + path);
                        deregisterSlaveNode(path);
                    } else {
                        logger.info("I become master node without replacing any node");
                    }
                    // Update self's path
                    path = s1;
                    break;
                case NODEEXISTS:
                    synchronized (this) {
                        isLeader = false;
                    }
                    registerSlaveNode();
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
        /*
         *  s is the path
         *  s1 is the node_name
         */
        public void processResult(int i, String s, Object o, String s1) {

            switch (KeeperException.Code.get(i)) {
                case CONNECTIONLOSS:
                    registerSlaveNode();
                    break;
                case OK:
                    logger.info("Registered slave node successfully");
                    logger.info("I am slave node " +  s1);
                    List<String> slaveNodes = getChildrenNodeName(rootSlaveName);
                    Collections.sort(slaveNodes);
                    int size = slaveNodes.size();

                    if(size >= 2) {
                        String last_node = slaveNodes.get(slaveNodes.size()-2);
                        logger.info("last node name " + last_node);
                        listenSlaveNode(rootSlaveName +  "/" + last_node);
                    } else {
                        masterExists();
                    }
                    path = s1;
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

    // Listen master node delete event and run as a master
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


    public class SlaveNodeWatcher implements Watcher {
        private String lastWatchNode = "";
        public String getLastWatchNode() {
            return lastWatchNode;
        }

        public void setLastWatchNode(String lastWatchNode) {
            this.lastWatchNode = lastWatchNode;
        }

        @Override
        public void process(WatchedEvent watchedEvent) {
            if(watchedEvent.getType() == Event.EventType.NodeDeleted) {
                String last_watch_node = lastWatchNode;
                logger.info("last watch node is" + last_watch_node);
                List<String> nodes = getChildrenNodeName(rootSlaveName);
                if(nodes.size() == 1) {
                    masterExists();
                } else {
                    Collections.sort(nodes);
                    int res = 0;
                    for(int i = 0; i < nodes.size(); i++) {
                        String node = nodes.get(i);
                        logger.info("node is " + node);
                        if(node.compareTo(last_watch_node) > 0 ) {
                            res  = i;
                            break;
                        }
                    }

                    if(res == 0) {
                        logger.info("I am listen master node ");
                        masterExists();
                    } else {
                        String listen_node = nodes.get(res-1);
                        logger.info("I will be listen " + listen_node + " slave node");
                        listenSlaveNode(listen_node);
                    }
                }
            }
        }
    }

    private AsyncCallback.StatCallback slaveExistsCallback = new AsyncCallback.StatCallback() {
        @Override
        public void processResult(int i, String s, Object o, Stat stat) {
            switch (KeeperException.Code.get(i)) {
                case CONNECTIONLOSS:
                    // ReCheck
                    listenSlaveNode(s);
                    break;
                case OK:
                    logger.info("listen slave node successfully : " + s);
                    break;
                default:
                    logger.info("something wrong to listen slave node, " + KeeperException.Code.get(i));
                    break;
            }

        }
    };

    public void process(WatchedEvent watchedEvent) {
        logger.info(watchedEvent);
    }

    public void stopZK() {
        try {
            zk.close();
        } catch (Exception e) {
            logger.info("something error ", e);
        }
    }

    public void listenSlaveNode(String nodeName) {
        SlaveNodeWatcher watcher = new SlaveNodeWatcher();
        watcher.setLastWatchNode(nodeName);

        zk.exists(nodeName, watcher, slaveExistsCallback, null);
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

    // Create slave root nodes
    public void bootstrap() {
        createParent(rootSlaveName, new byte[0]);
    }

    // As a master run
    public void runForMaster() {
        zk.create(masterNodeName, getUid().getBytes(), OPEN_ACL_UNSAFE,  CreateMode.EPHEMERAL, createMasterNodeCallback, null);
    }

    // Check whether node is Master node
    private void checkMaster() {
        zk.getData(masterNodeName, false, masterCheckCallback, null);
    }

    private void registerSlaveNode() {
        // Create ephemeral node
        zk.create(rootSlaveName+slavePrefix, (getUid()).getBytes(), ZooDefs.Ids.OPEN_ACL_UNSAFE, CreateMode.EPHEMERAL_SEQUENTIAL, createSlaveCallback, null);
    }


    private void deregisterSlaveNode(String node) {
        try {

            zk.delete(node, -1);
            logger.info("delete slave node " + path + " successfully");
        } catch (Exception e) {
            logger.error(e);
        }
    }


    private String getUid() {
        return localHostName;
    }

    private List<String> getChildrenNodeName(String root) {
        try {
            List<String> nodes = zk.getChildren(root, false);
            return nodes;
        } catch (KeeperException e) {
            return new ArrayList<String>();
        } catch(InterruptedException e) {
            return new ArrayList<String>();
        }
    }

}
