package com.itsm.collecting.queue;

import com.itsm.collecting.util.StringUtil;
import com.rabbitmq.client.*;
import org.apache.log4j.Logger;

import java.io.IOException;
import java.util.concurrent.TimeoutException;

/**
 * Created by bruce on 16-11-28.
 */
public class StoreDataConsumerNode {

    private final static String exchange_name = "topic";
    private final static String host = StringUtil.getRabbitMQIp();
    private static final Logger logger = Logger.getLogger(StoreDataConsumerNode.class);
    private static String[] bind_key = new String[] {
            "redis",
            "memcached",
            "rabbitmq"
    };


    public static void main(String[] args) throws TimeoutException, IOException, InterruptedException {
        ConnectionFactory factory = new ConnectionFactory();
        factory.setHost(host);
        Connection connection = factory.newConnection();
        Channel channel = connection.createChannel();
        channel.exchangeDeclare(exchange_name, "topic");
        String queue_name = channel.queueDeclare().getQueue();

        for(String key : bind_key) {
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
    }
}
