package com.itsm.collecting;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

import org.apache.ibatis.session.SqlSession;
import org.apache.log4j.Logger;

import com.itsm.collecting.dao.DatabaseBasicInfoMapper;
import com.itsm.collecting.dao.HostBasicInfoMapper;
import com.itsm.collecting.model.DatabaseBasicInfo;
import com.itsm.collecting.model.HostBasicInfo;
import com.itsm.collecting.util.Constants;
import com.itsm.collecting.util.DBCollectingTask;
import com.itsm.collecting.util.HostCollectingTask;
import com.itsm.collecting.util.JedisPoolUtils;
import com.itsm.collecting.util.SqlSessionUtil;

import redis.clients.jedis.Jedis;

/**
 * Created by CM on 2016/7/14.
 */
public class CollectingServer {
    private static Logger logger = Logger.getLogger(CollectingServer.class);

    private static  ScheduledExecutorService host_es;
    private static  ScheduledExecutorService db_es;


    public CollectingServer() {
        int core_num = Runtime.getRuntime().availableProcessors();
        logger.info("core num is " + core_num);

        if(core_num > 2) {
            host_es =  Executors.newScheduledThreadPool(core_num/2);
            db_es = Executors.newScheduledThreadPool(core_num - core_num/2);
        } else {
            host_es = Executors.newScheduledThreadPool(2);
            db_es = Executors.newScheduledThreadPool(2);
        }

    }




    public static void main(String[] args) throws Exception {

        JedisPoolUtils.initPool();
        Jedis jedis = JedisPoolUtils.getResource();
        CollectingServer server = new CollectingServer();
        
        ConcurrentHashMap<String,Future> host_future_map = new ConcurrentHashMap<String,Future>();
        ConcurrentHashMap<String,Future> db_future_map = new ConcurrentHashMap<String,Future>();
        
        try{        	       	
            List<String> host = jedis.lrange(Constants.COLLECTING_HOST_INFO, 0, -1);

            List<String> host_ip_type_info = new ArrayList<String>();

            if(jedis == null){
                logger.error("redis can't initialized");
                return;
            }

            // redis 中没有需要监控的主机信息
            if(host == null || host.size() == 0) {
                SqlSession s = SqlSessionUtil.getSqlSession().openSession(true);

                List<HostBasicInfo> host_info;
                try {
                    HostBasicInfoMapper mapper = s.getMapper(HostBasicInfoMapper.class);
                    host_info = mapper.selectAllNeedToCollectHost();

                    for (HostBasicInfo h : host_info) {
                    	
                        String ip = h.getHostIp();
                        String os = h.getHostOs();
                        Integer id = h.getHostId();
                        host_ip_type_info.add(ip + ":" + os + ":" + id);
                        
                    	HostCollectingTask task = new HostCollectingTask(host_future_map,h);
                        Future future = host_es.scheduleAtFixedRate(task, 1, 5, TimeUnit.MINUTES);
                        host_future_map.put(h.getHostIp(), future);
                    }

                    jedis.lpush(Constants.COLLECTING_HOST_INFO, host_ip_type_info.toArray(new String[host_ip_type_info.size()]));

                } catch(Exception e) {
                    e.printStackTrace();
                }  finally {
                    logger.info("close right");
                    s.close();
                }

            } else {
                for(String h : host) {
                    String[] detail = h.split(":");
                    assert(detail.length == 3);
                    HostBasicInfo info = new HostBasicInfo();
                    info.setHostIp(detail[0]);
                    info.setHostOs(detail[1]);
                    info.setHostId(Integer.parseInt(detail[2]));
                    HostCollectingTask task = new HostCollectingTask(host_future_map,info);
                    Future future = host_es.scheduleAtFixedRate(task, 1, 5, TimeUnit.MINUTES);
                    host_future_map.put(info.getHostIp(), future);
                }
            }

        } catch (Exception e) {
            // Destroy pool
            JedisPoolUtils.destroyPool();
            logger.error(e);
        } finally {
             JedisPoolUtils.returnResource(jedis);
        }



        SqlSession s = null;
        Jedis db_jedis = null;

        
        try {
            JedisPoolUtils.initPool();
            db_jedis = JedisPoolUtils.getResource();
            s = SqlSessionUtil.getSqlSession().openSession(true);

            DatabaseBasicInfoMapper mapper = s.getMapper(DatabaseBasicInfoMapper.class);
            List<String> db_list = db_jedis.lrange(Constants.COLLECTING_DB_INFO, 0, -1);
            List<String> db_info_str = new ArrayList<String>();


            if(db_list == null || db_list.size() == 0) {
                logger.info("redis empty ");
                List<DatabaseBasicInfo> dbs = mapper.selectAllDatabaseInUse();
                for(DatabaseBasicInfo db: dbs){
                	if(db!=null){
                		String db_ip = db.getDbIp();
                        String db_port = db.getDbPort();
                        String db_name = db.getDbName();
                        String db_type = db.getDbType();
                        String db_user = db.getDbUsername();
                        logger.info("db user " + db_user);
                        String db_pass = db.getDbPassword();
                        db_info_str.add(db_ip + ":" + db_port + ":" + db_type + ":" + db_user + ":" + db_pass);
                        db_jedis.lpush(Constants.COLLECTING_DB_INFO, db_ip + ":" + db_port + ":" + db_type + ":" + db_user + ":" + db_pass);
                		DBCollectingTask collecting_task = new DBCollectingTask(db_future_map,db);
                		Future future=db_es.scheduleAtFixedRate(collecting_task, 1, 20, TimeUnit.MINUTES);
                		db_future_map.put(db.getDbIp()+":"+db.getDbType(), future);
                	}
                }
//                db_jedis.lpush(Constants.COLLECTING_DB_INFO, db_info_str.toArray(new String[db_info_str.size()]));


            } else {
                for(String db : db_list) {
                    String[] detail = db.split(":");
                    DatabaseBasicInfo info = new DatabaseBasicInfo();
                    info.setDbIp(detail[0]);
                    info.setDbPort(detail[1]);
                    info.setDbType(detail[2]);
                    info.setDbUsername(detail[3]);
                    info.setDbPassword(detail[4]);
                    if(detail[2].equals("oracle")){
                    	info.setDbOracleSid(detail[5]);
                    }
                    logger.info("db user "+info.getDbUsername());
                    DBCollectingTask collecting_task = new DBCollectingTask(db_future_map,info);
                    Future future = db_es.scheduleAtFixedRate(collecting_task, 1, 20, TimeUnit.MINUTES);
                    db_future_map.put(info.getDbIp()+":"+info.getDbType(), future);
                }
            }

        } catch (Exception e) {
            logger.error("some thing wrong ", e);
        } finally {
            if(s != null) {
                s.close();
            }
            JedisPoolUtils.returnResource(db_jedis);
        }

        TestCollectingServiceServer test_server = new TestCollectingServiceServer(4444,host_es,db_es,host_future_map,db_future_map);
        test_server.start();

    }


}
