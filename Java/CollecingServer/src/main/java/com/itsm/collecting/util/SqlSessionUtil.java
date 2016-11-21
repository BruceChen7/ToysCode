package com.itsm.collecting.util;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.apache.log4j.Logger;

import java.io.IOException;
import java.io.Reader;

/**
 * Created by CM on 2016/7/20.
 */
public class SqlSessionUtil {

    private static Logger logger = Logger.getLogger(SqlSessionUtil.class);
    private static SqlSessionFactory factory = null;


    public static synchronized SqlSessionFactory getSqlSession() {
        String resource = "mybatis-config.xml";

        Reader reader;
        try {
            if(factory == null) {
                reader = Resources.getResourceAsReader(resource);
                SqlSessionFactory ssf = new SqlSessionFactoryBuilder().build(reader);
                factory = ssf;
                return ssf;
            } else {
                return factory;
            }


        } catch (IOException e) {
            logger.error("xml is error ", e);
        }
        return null;

    }

}
