package com.itsm.collecting.util;

import java.util.Properties;
import org.apache.log4j.*;

/**
 * Created by CM on 2016/7/21.
 */
public class StringUtil {

    private static Logger logger = Logger.getLogger(StringUtil.class);

    public static  String getRedisIp() {
        return getPropertiesValue("redis.properties", "ip");
    }

    public static String getRedisPort() {
        return getPropertiesValue("redis.properties", "port");
    }

    public static String getRedisTimeout() {
        return getPropertiesValue("redis.properties", "timeout");
    }

    public static String getRedisPassword() {
        return getPropertiesValue("redis.properties", "password");
    }




    public static synchronized String getPropertiesValue(String configFilePath, String Key)  {

        String result = null;
        Properties properties = new Properties();

        try {
            properties.load(StringUtil.class.getClassLoader().getResourceAsStream(configFilePath));
            result = properties.getProperty(Key);
        } catch(Exception e) {
            logger.error("错误栈", e);
            logger.error("属性文件为 "+configFilePath+" 读取属性文件失败,请检查原因");

        }
        return result;

    }



    public static boolean isStrNull(String str) {
        if(str == null || str.equals("")) {
            return true;
        } else {
            return false;
        }
    }

}
