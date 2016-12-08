package com.itsm.collecting.node;

import org.apache.log4j.Logger;
import org.apache.zookeeper.*;
import org.apache.zookeeper.data.Stat;

import java.util.Random;

import static org.apache.zookeeper.ZooDefs.Ids.OPEN_ACL_UNSAFE;

/**
 * Created by bruce on 16-11-21.
 */
public class CollectingMasterNode implements Watcher {

    private ZooKeeper zk;
    private String hostPort;
    private static Logger logger = Logger.getLogger(CollectingMasterNode.class);
    private boolean isLeader = false;
    private String serverId = Integer.toHexString(new Random().nextInt());

    public CollectingMasterNode(String hostPort) {
        this.hostPort = hostPort;
    }


    AsyncCallback.StringCallback  createParentCallback = new AsyncCallback.StringCallback() {
        public void processResult(int i, String s, Object o, String s1) {
             switch (KeeperException.Code.get(i)) {
                 case CONNECTIONLOSS:
                     createParent(s, (byte[])o);
                     break;
                 case OK:
                     logger.info("parent created");
                     break;
                 case NODEEXISTS:
                     logger.info("");
             }
        }
    };


    // 创建zookeeper 连接
    public void startZK() {
        try {
            zk = new ZooKeeper(hostPort, 15000, this);
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
            logger.info("I am " );

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
        createParent("/workers", new byte[0]);
        createParent("/assign", new byte[0]);
        createParent("/tasks", new byte[0]);
        createParent("/assign", new byte[0]);
    }

    // 作为主节点中的管理接运行
    public void runForMaster() throws  InterruptedException {
        while (true) {
            try {
                zk.create("/master", serverId.getBytes(), OPEN_ACL_UNSAFE, CreateMode.EPHEMERAL);
                isLeader = true;
                break;
            } catch (KeeperException.NodeExistsException e) {
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
                byte data[] = zk.getData("/master", false, stat);
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
        logger.info(watchedEvent);
    }

    public void stopZK() throws  Exception {
        zk.close();
    }

    public static  void main(String args[]) throws Exception {
        CollectingMasterNode c = new CollectingMasterNode("127.0.0.1:2181");
        c.startZK();
        c.runForMaster();

        if(c.isLeaderMaster()) {
            logger.info("is master");
        } else {
            logger.info("is not master");
        }
        c.stopZK();
    }
}
