package com.itsm.collecting.node;

import org.apache.log4j.Logger;
import org.apache.zookeeper.KeeperException;
import org.apache.zookeeper.WatchedEvent;
import org.apache.zookeeper.Watcher;
import org.apache.zookeeper.ZooKeeper;
import org.apache.zookeeper.data.Stat;

/**
 * Created by bruce on 16-11-25.
 */
/*
 * It's a class to watch Zookeeper client and master node
 */
public class CollectingNodeWatcher implements Watcher {
    private ZooKeeper zk;
    private String hostPort;
    private static Logger  logger = Logger.getLogger(CollectingNodeWatcher.class);

    public CollectingNodeWatcher(String port) {
        hostPort = port;
    }

    public void start() throws Exception {
        zk = new ZooKeeper(hostPort, 15000, this);
    }

    public void process(WatchedEvent watchedEvent) {
        logger.info(watchedEvent);
    }


    void listenState() throws KeeperException {
        try {
            Stat stat = new Stat();
            byte[] masterData= zk.getData("/master", false, stat);
        } catch(KeeperException.NoNodeException e) {
            logger.error("No master");
        } catch (InterruptedException e) {
            logger.info("interrupt");
        }

        logger.info("Work nodes are here ");

        try {
            for (String w : zk.getChildren("/works", false)) {
                logger.info(w);
            }
        } catch (InterruptedException e) {
            logger.info("interrrupt in get slave nod");
        }
    }
}
