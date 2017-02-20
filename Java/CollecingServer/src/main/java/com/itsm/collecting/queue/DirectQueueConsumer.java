package com.itsm.collecting.queue;

import com.itsm.collecting.service.IDirectQueueConsumeTask;
import com.rabbitmq.client.*;
import org.apache.log4j.Logger;

import java.io.IOException;

/**
 * Created by bruce on 16-11-28.
 */
public class DirectQueueConsumer {

    private final String exchange_name ;
    private final String host ;
    private final String routine_key;
    private final String queue_name;
    private static final Logger logger = Logger.getLogger(DirectQueueConsumer.class);

    public DirectQueueConsumer(String host, String exchange_name, String queue_name, String routine_key) {
        this.exchange_name = exchange_name;
        this.host = host;
        this.routine_key = routine_key;
        this.queue_name = queue_name;
    }

    public void directQueueConsume(IDirectQueueConsumeTask task) {
        try {
                ConnectionFactory factory = new ConnectionFactory();
                factory.setHost(host);
                Connection connection = factory.newConnection();
                Channel ch = connection.createChannel();
                ch.exchangeDeclare(exchange_name, "direct", true);
                ch.queueDeclare(queue_name, true, false, false, null);
                ch.queueBind(queue_name, exchange_name, routine_key);
                logger.info("wait for  messages. to exit  press Ctrl + C");
                Consumer consumer = new DefaultConsumer(ch) {
                @Override
                public void handleDelivery(String consumerTag, Envelope envelop, AMQP.BasicProperties p, byte[] body) throws IOException {
                    task.consume(body);
                    String message = new String(body, "UTF-8");
                    logger.info("receive  " + message);

                }
            };
                ch.basicConsume(queue_name, true, consumer);
        } catch (Exception e) {
            logger.error("something error, ", e);
        }

    }

    public static void main(String[] args) throws Exception {
        IDirectQueueConsumeTask t = new IDirectQueueConsumeTask() {
            @Override
            public void consume(byte[] data) {
                try {
                    String message = new String(data, "UTF-8");
                } catch (Exception e) {
                    logger.info("something error ", e);
                }
            }
        };

        DirectQueueConsumer c  = new  DirectQueueConsumer("localhost", "host", "host_queue", "host_data");
        c.directQueueConsume(t);

    }
}
