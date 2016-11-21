package com.itsm.collecting.util;

import redis.clients.jedis.JedisPubSub;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;

import org.apache.log4j.*;

/**
 * Created by CM on 2016/8/18.
 */
public class MonitorSubscriber extends JedisPubSub{
    private ScheduledExecutorService es_;
    private static Logger logger = Logger.getLogger(MonitorSubscriber.class);

    public MonitorSubscriber(ScheduledExecutorService es) {
        es_ = es;
    }

    // 存在消息的回调
    @Override
    public void onMessage(String channel, String message) {
        logger.info("receive message on channel " + channel + " which message is " + message);
        String[] msg = message.split(":");

        assert(msg.length == 2);
        String ip = msg[0];
        String os = msg[1];

        logger.info("ip is " + ip);
        logger.info("os is"  + os);
        ScheduledFuture<Integer> future  = es_.schedule(new TestHostMonitorUtil(ip, os), 0, TimeUnit.SECONDS);

        try {
            logger.info("task运行结果 "+future.get());
            int result = future.get();
            if(result == 1) {

            } else {
                
            }
        } catch (InterruptedException e) {
            logger.error("Interruption Exception ", e);
        } catch (ExecutionException e) {
            e.printStackTrace();
        }
    }


    @Override
    public void onSubscribe(String channel, int subscribedChannels) {

    }

    @Override
    public void onUnsubscribe(String channel, int subscribedChannels) {
    }


}
