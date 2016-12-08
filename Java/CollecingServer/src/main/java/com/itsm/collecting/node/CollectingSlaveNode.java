package com.itsm.collecting.node;

import org.apache.log4j.Logger;
import org.apache.zookeeper.*;

import java.io.IOException;
import java.util.Random;

/**
 * Created by bruce on 16-11-25.
 */
public class CollectingSlaveNode  implements Watcher {
    private  static Logger logger = Logger.getLogger(CollectingSlaveNode.class);
    private String  hostPort;
    private ZooKeeper zk;
    private String serverId = Integer.toHexString(new Random().nextInt());
    private String ip;

    public CollectingSlaveNode(String ip, String hostPort) {
        this.hostPort = hostPort;
        this.ip = ip;
    }


    public void startZK() throws IOException {
        zk = new ZooKeeper(hostPort, 15000, this);
    }

    public void process(WatchedEvent watchedEvent) {
        logger.info(watchedEvent.toString() + ", " + hostPort );
    }


    void register() {
        zk.create("/works/worker-"+ ip + "-" + hostPort + "-"+ serverId, "Idle".getBytes(), ZooDefs.Ids.OPEN_ACL_UNSAFE, CreateMode.EPHEMERAL, createWorkCallback, null);

    }

    private AsyncCallback.StringCallback createWorkCallback = new AsyncCallback.StringCallback() {
        public void processResult(int i, String s, Object o, String s1) {

            switch (KeeperException.Code.get(i)) {
                case CONNECTIONLOSS:
                    register();
                    break;
                case OK:
                    logger.info("Registered sucessfully " + getNodeUid());
                case NODEEXISTS:
                    logger.warn("Already registerd : " + serverId);
                    break;
                default:
                    logger.error("something wrong :" +   KeeperException.create(KeeperException.Code.get(i), s));

            }
        }
    };
    private String getNodeUid() {
        return ip + "-" + hostPort + "-" + serverId;
    }
}
