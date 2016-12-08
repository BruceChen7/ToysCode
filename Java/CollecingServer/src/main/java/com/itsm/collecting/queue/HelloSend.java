package com.itsm.collecting.queue;

import com.rabbitmq.client.Channel;
import com.rabbitmq.client.Connection;
import com.rabbitmq.client.ConnectionFactory;
import org.apache.log4j.Logger;

/**
 * Created by bruce on 16-11-28.
 */
public class HelloSend {
    private final  static String QUEUE_NAME = "hello";
    private final static Logger logger = Logger.getLogger(HelloSend.class);
    public static void main(String[] args) throws Exception {
        ConnectionFactory factory = new ConnectionFactory();
        factory.setHost("localhost");
        Connection connection = factory.newConnection();
        Channel channel = connection.createChannel();
        // just binding a queue to a exchange
        channel.queueDeclare(QUEUE_NAME, false, false, false, null);
        String message = "Hello world";
        channel.basicPublish("", QUEUE_NAME, null, message.getBytes("UTF-8"));
        logger.info("[x] sent " + message + "'");

        channel.close();
        connection.close();

    }
}
