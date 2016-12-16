package com.itsm.collecting.node;

import com.itsm.collecting.util.StringUtil;
import com.rabbitmq.client.*;
import org.apache.log4j.Logger;

import java.io.IOException;

/**
 * Created by bruce on 16-12-14.
 */
public class ProducerMasterRabbitMQNode extends RabbitMQNodeTask {
    private final static String exchange_name = "topic";
    private final static String host = StringUtil.getRabbitMQIp();
    private static final Logger logger = Logger.getLogger(ProducerMasterRabbitMQNode.class);


    private final String masterPath;


    private final String slavePath;

    private static String[] bind_key = new String[] {
            "redis"
    };


    public ProducerMasterRabbitMQNode(String masterPath, String slaverPath) {
        this.masterPath = masterPath;
        this.slavePath = slaverPath;
    }

    public String getMasterPath() {
        return masterPath;
    }

    public String getSlavePath() {
        return slavePath;
    }


    public static void main(String[] args) throws  Exception {
        ProducerMasterRabbitMQNode node = new ProducerMasterRabbitMQNode("/master", "/slavers");
        node.startTask(node.getMasterPath(), node.getSlavePath());
    }

    @Override
    public void concreteWork() {
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
                    logger.info(p.getContentType());
                    String message = new String(body, "UTF-8");
                    logger.info("receive  " + message);

                }
            };
            channel.basicConsume(queue_name, true, consumer);

        } catch (Exception e) {

        }

    }
}
