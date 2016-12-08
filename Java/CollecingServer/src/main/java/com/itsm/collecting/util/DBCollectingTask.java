package com.itsm.collecting.util;

import java.util.List;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.Future;

import org.apache.log4j.Logger;

import com.itsm.collecting.model.DatabaseBasicInfo;
import com.itsm.collecting.service.IDBCollectingTask;
import com.itsm.collecting.service.MysqlCollectingTask;
import com.itsm.collecting.service.OracleCollectingTask;
import com.itsm.collecting.service.SqlServerCollectingTask;

import redis.clients.jedis.Jedis;

/**
 * Created by CM on 2016/8/25.
 */
public class DBCollectingTask implements Runnable {
    private DatabaseBasicInfo db;
    private ConcurrentHashMap<String,Future> db_future_map;
    private static final Logger logger = Logger.getLogger(DBCollectingTask.class);

    public DBCollectingTask(ConcurrentHashMap<String,Future> db_future_map,DatabaseBasicInfo db) {
        this.db = db;
        this.db_future_map = db_future_map;
    }

    @Override
    public void run() {

        String db_type = db.getDbType();
        String ip = db.getDbIp();
        String port = db.getDbPort();
        String db_name = db.getDbName();
        String sid = db.getDbOracleSid();
        db_name = db_name == null ? "" : db_name;


        String user_name = db.getDbUsername();
        String pass = db.getDbPassword();
        
        
        String value = ip + ":" + port + ":" + db_type + ":" + user_name + ":" + pass ;
        if(db_type.equals("oracle")){
        	value = value+ ":" +sid;
        }
        JedisPoolUtils.initPool();
        Jedis jedis = JedisPoolUtils.getResource();
        List<String> coll_db_list = jedis.lrange(Constants.COLLECTING_DB_INFO, 0, -1);
        JedisPoolUtils.returnResource(jedis);

        if(!coll_db_list.contains(value)){
        	Future future = db_future_map.remove(ip+":"+db_type);
        	future.cancel(true);
        	logger.info("DataBase from " +value+ "collecting has been cancled");
        	return;
        }

        if(!StringUtil.isStrNull(db_type)) {
            if(db_type.equals(Constants.MYSQL_DB)) {
                IDBCollectingTask task = new MysqlCollectingTask();
                task.runCollectJob(ip, port, db_name, user_name, pass);
            }
            else if(db_type.equals(Constants.SQL_SERVER)){
            	IDBCollectingTask task = new SqlServerCollectingTask();
            	task.runCollectJob(ip, port, db_name, user_name, pass);
            }
            else if(db_type.equals(Constants.ORACLE_DB)){
            	IDBCollectingTask task = new OracleCollectingTask();
            	task.runCollectJob(ip, port, sid, user_name, pass);
            }
            else{
            	return;
            }
        }


    }
}
