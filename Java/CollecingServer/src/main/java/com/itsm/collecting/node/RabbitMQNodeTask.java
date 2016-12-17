package com.itsm.collecting.node;


import org.apache.log4j.*;

/**
 * Created by bruce on 16-12-13.
 */
public abstract class RabbitMQNodeTask {
    private static Logger logger = Logger.getLogger(RabbitMQNodeTask.class);
    public abstract void concreteWork();

    public void startTask(String master_root, String slave_root) {
        PullCollectingNode node = new PullCollectingNode(master_root, slave_root, this);
        node.startZK();
        node.bootstrap();
        node.runForMaster();

        synchronized (this) {
            while (!node.isLeaderMaster()) {
                try {
                    this.wait();
                } catch (InterruptedException e) {
                    logger.error(e);
                }
            }
        }

        concreteWork();

    }
}
