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

    AsyncCallback.StringCallback  createParentCallback = new AsyncCallback.StringCallback() {
        public void processResult(int i, String s, Object o, String s1) {
             switch (KeeperException.Code.get(i)) {
                 case CONNECTIONLOSS:
                     createParent(s, (byte[])o);
                     break;
                 case OK:
                     logger.info("parent created sucessfully");
                     break;
                 case NODEEXISTS:
                     logger.info("parent has been created before");
             }
        }
    };


    // 创建zookeeper 连接
    public void startZK() {
        try {
            String addr = ip + ":" + hostPort;
            zk = new ZooKeeper(addr, 15000, this);
        } catch (Exception e) {

        }
    }

    private AsyncCallback.StringCallback masterCreateCallback = new AsyncCallback.StringCallback() {
        public void processResult(int i, String s, Object o, String s1) {
            switch (KeeperException.Code.get(i)) {
                case CONNECTIONLOSS:
                    checkMaster();
                    return;
                case OK:
                    isLeader = true;
                    break;
                default:
                    isLeader = false;
            }
        }
    };

    public boolean isLeaderMaster() {
        return isLeader;
    }

    public void createParent(String path, byte[] data) {
        zk.create(path, data, ZooDefs.Ids.OPEN_ACL_UNSAFE, CreateMode.PERSISTENT, createParentCallback, data);
    }

    // 创建其他的work
    public void boostrap() {
        createParent(slaveNodeName, new byte[0]);
    }

    // 作为主节点中的管理接运行
    public void runForMaster() throws  InterruptedException {
        while (true) {
            try {
                // 创建临时节点，挂掉了好从slave节点中选取一个从节点来代替
                zk.create(masterNodeName, serverId.getBytes(), OPEN_ACL_UNSAFE, CreateMode.EPHEMERAL);
                isLeader = true;
                break;
            } catch (KeeperException.NodeExistsException e) {
                logger.info("master node exists");
                isLeader = false;
                break;
            } catch (KeeperException.ConnectionLossException e) {

            } catch (KeeperException e) {
                logger.info("something wrong", e);
            }

            if(checkMaster())
                break;
        }

    }

    // Whether this Server is Master node
    private boolean checkMaster() {
        while(true) {
            try {
                Stat stat = new Stat();
                byte data[] = zk.getData(masterNodeName, false, stat);
                isLeader = new String(data).equals(serverId);
                return true;

            } catch (KeeperException.NoNodeException e) {
                return false;
            } catch (InterruptedException e) {
                return false;
            } catch (KeeperException e) {
                return false;
            }
        }

    }

    public void process(WatchedEvent watchedEvent) {
        logger.info("hello world");
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
        c.boostrap();
        c.runForMaster();
        if(c.isLeaderMaster()) {

        } else {
            c.registerSlaveNode();
            logger.info("is not master" );
        }
        Thread.sleep(10000);
        c.stopZK();
    }

    public void registerSlaveNode() {
        String name = slaveNodeName + "/slaver-" + getUid();
        logger.info("name is " + name);
        zk.create(name, "Idle".getBytes(), ZooDefs.Ids.OPEN_ACL_UNSAFE, CreateMode.EPHEMERAL, createWorkCallback, null);
    }

    private AsyncCallback.StringCallback createWorkCallback = new AsyncCallback.StringCallback() {
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


    private String getUid() {
        return serverId + "-" + localHostName;
    }

}
