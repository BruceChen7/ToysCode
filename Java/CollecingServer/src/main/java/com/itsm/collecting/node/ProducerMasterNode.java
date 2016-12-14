package com.itsm.collecting.node;

import com.itsm.collecting.util.StringUtil;
import com.rabbitmq.client.*;
import org.apache.log4j.Logger;

import java.io.IOException;
import java.util.concurrent.TimeoutException;

/**
 * Created by bruce on 16-12-14.
 */
public class ProducerMasterNode  implements  INodeTask {
    private final static String exchange_name = "topic";
    private final static String host = StringUtil.getRabbitMQIp();
    private static final Logger logger = Logger.getLogger(ProducerMasterNode.class);

    private static String[] bind_key = new String[] {
            "redis"
    };

    @Override
    public void startSlaveTask() {
        logger.info("start slave Task");
    }

    @Override
    public void startMasterTask()  {
        ConnectionFactory factory = new ConnectionFactory();
        factory.setHost(host);
        try {
            Connection connection = factory.newConnection();
            Channel channel = connection.createChannel();
            channel.exchangeDeclare(exchange_name, "topic", true);
            String queue_name = channel.queueDeclare().getQueue();

            for (String key : bind_key) {
                channel.queueBind(queue_name, exchange_name, key);
            }
            logger.info("wait for  messages. to exit  press Ctrl + C");

            Consumer consumer = new DefaultConsumer(channel) {
                @Override
                public void handleDelivery(String consumerTag, Envelope envelop, AMQP.BasicProperties p, byte[] body) throws IOException {
                    String message = new String(body, "UTF-8");
                    logger.info("receive  " + message);

                }
            };
            channel.basicConsume(queue_name, true, consumer);

        } catch (Exception e) {

        }
    }

    public static void main(String[] args) throws Exception {
        ProducerMasterNode produce_node = new ProducerMasterNode();
        CollectingNode node = new CollectingNode("/master", "/slavers", produce_node);
        node.startZK();
        node.bootstrap();
        node.runForMaster();

        synchronized (node) {
            while (!node.isLeaderMaster()) {
                try {
                    node.wait();
                } catch (InterruptedException e) {
                    logger.error(e);
                }
            }
        }

        produce_node.startMasterTask();

    }
}
