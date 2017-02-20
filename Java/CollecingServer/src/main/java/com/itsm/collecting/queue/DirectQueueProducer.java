package com.itsm.collecting.queue;

import com.rabbitmq.client.Channel;
import com.rabbitmq.client.Connection;
import com.rabbitmq.client.ConnectionFactory;
import org.apache.log4j.Logger;

/**
 * Created by bruce on 16-11-28.
 */
public class DirectQueueProducer {
    private final  String exchange_name;
    private final String host ;
    private final String routine_key;
    private final String queue_name;
    private final static Logger logger = Logger.getLogger(DirectQueueProducer.class);

    public DirectQueueProducer(String host, String exchange_name, String queue_name, String routine_key) {
        this.exchange_name = exchange_name;
        this.host = host;
        this.queue_name = queue_name;
        this.routine_key = routine_key;
    }

    public  void produce(byte[] msg){
        try {
            ConnectionFactory factory = new ConnectionFactory();
            factory.setHost("localhost");
            Connection connection = factory.newConnection();
            Channel channel = connection.createChannel();
            channel.queueDeclare(queue_name, true, false, false, null);
            channel.basicPublish(exchange_name, routine_key, null, msg);

            logger.info("[x] sent " + msg + "'");

            channel.close();
            connection.close();
        } catch (Exception e) {

            logger.error("something error ", e);
        }
    }

    public static void main(String[] args) {
        DirectQueueProducer p = new DirectQueueProducer("localhost", "host", "host_queue", "host_data");
        int i = 10;
        while(i != 0) {
            p.produce("hello world".getBytes());
            i--;
        }
    }
}
