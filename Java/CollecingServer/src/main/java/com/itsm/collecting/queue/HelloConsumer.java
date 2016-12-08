package com.itsm.collecting.queue;

import com.rabbitmq.client.*;
import org.apache.log4j.Logger;

import java.io.IOException;
import java.util.concurrent.TimeoutException;

/**
 * Created by bruce on 16-11-28.
 */
public class HelloConsumer {
    private final static String QUEUE_NAME  = "hello";
    private static final Logger logger = Logger.getLogger(HelloConsumer.class);


    public static void main(String[] args) throws TimeoutException, IOException, InterruptedException {
        ConnectionFactory factory = new ConnectionFactory();
        factory.setHost("localhost");
        Connection connection = factory.newConnection();
        Channel channel = connection.createChannel();
        channel.queueDeclare(QUEUE_NAME, false, false, false, null);
        logger.info("wait for  messages. to exit  press Ctrl + C");

        Consumer consumer = new DefaultConsumer(channel) {
            @Override
            public void handleDelivery(String consumerTag, Envelope envelop, AMQP.BasicProperties p, byte[] body) throws IOException {
                String message = new String(body, "UTF-8");
                logger.info("receive  " + message);

            }
        };
        channel.basicConsume(QUEUE_NAME, true, consumer);
    }
}
