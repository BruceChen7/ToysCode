package com.itsm.collecting.util;

import redis.clients.jedis.Jedis;
import redis.clients.jedis.JedisPool;
import redis.clients.jedis.JedisPoolConfig;

import org.apache.log4j.*;

/**
 * Created by CM on 2016/7/21.
 */
public class JedisPoolUtils {
    private static JedisPool pool;
    private static Logger logger = Logger.getLogger(JedisPoolUtils.class);

    private static void createJedisPool(String ip, int port, int timeout) {

        // 建立连接池配置参数
        JedisPoolConfig config = new JedisPoolConfig();

        // 设置最大连接数
        config.setMaxTotal(150);

        // 设置最大阻塞时间，记住是毫秒数milliseconds
        config.setMaxWaitMillis(2000);

        // 设置空闲连接
        config.setMaxIdle(10);


        // 创建连接池
        pool = new JedisPool(config, ip, port, timeout);

    }

    public static synchronized void initPool() {
        if(pool == null) {
            logger.info("init jedis pool");
            String ip = StringUtil.getRedisIp();
            int port = Integer.parseInt(StringUtil.getRedisPort());
            int timeout = Integer.parseInt(StringUtil.getRedisTimeout());
            createJedisPool(ip, port, timeout);
        }
    }

    // JedisPool is thread safe
    public  static  Jedis getResource() {
        if(pool == null) {
            return null;
        } else {
            Jedis jedis = pool.getResource();
            jedis.auth(StringUtil.getRedisPassword());
            return jedis;
        }
    }


    public  static  void returnResource(Jedis redis) {
        if (redis != null) {
            logger.info("return resource redis");
            pool.returnResource(redis);
        }
    }

    public static  void destroyPool() {
        if(pool != null) {
            pool.destroy();
        }

    }


}
