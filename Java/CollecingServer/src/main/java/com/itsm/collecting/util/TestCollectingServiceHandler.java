package com.itsm.collecting.util;

import java.util.List;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;

import org.apache.log4j.Logger;

import com.google.gson.Gson;
import com.itsm.collecting.model.DatabaseBasicInfo;
import com.itsm.collecting.model.HostBasicInfo;
import com.itsm.collecting.model.TestCollectingInfo;

import io.netty.buffer.Unpooled;
import io.netty.channel.ChannelFutureListener;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInboundHandlerAdapter;
import io.netty.util.CharsetUtil;
import redis.clients.jedis.Jedis;


/**
 * Created by CM on 2016/8/25.
 */
public class TestCollectingServiceHandler extends ChannelInboundHandlerAdapter {

    private  static Logger logger = Logger.getLogger(TestCollectingServiceHandler.class);
    
    private final ScheduledExecutorService host_es;
    
    private final ScheduledExecutorService db_es;
    
    private final ConcurrentHashMap<String,Future> host_future_map;
    
    private final ConcurrentHashMap<String,Future> db_future_map;

    
    public TestCollectingServiceHandler(ScheduledExecutorService host_es,ScheduledExecutorService db_es,ConcurrentHashMap<String,Future> host_future_map,ConcurrentHashMap<String,Future> db_future_map){
    	this.host_es = host_es;
    	this.db_es =db_es;
    	this.host_future_map = host_future_map;
    	this.db_future_map = db_future_map;
    }

    @Override
    public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
    	logger.info(msg.toString());
    	final Gson gson = new Gson();
        Integer res=0;
        final TestCollectingInfo test_info  = gson.fromJson(msg.toString(), TestCollectingInfo.class);
        String type = test_info.getType();
        logger.info("test info type " + test_info.getType());
        if(type.equals("0")) {
            String ip = test_info.getIp();
            String os = test_info.getOs();
            res = testHostCollecting(ip, os);
            JedisPoolUtils.initPool();
        	Jedis jedis = JedisPoolUtils.getResource();
        	List<String> coll_host_list = jedis.lrange(Constants.COLLECTING_HOST_INFO, 0, -1);
        	String value_string = test_info.getIp() + ":" + test_info.getOs() + ":" + test_info.getId();
            if(res==1){           	
            	if(!coll_host_list.contains(value_string)){
            		jedis.lpush(Constants.COLLECTING_HOST_INFO, value_string);
                	HostBasicInfo info = new HostBasicInfo();
                	info.setHostIp(test_info.getIp());
                	info.setHostOs(test_info.getOs());
                	info.setHostId(test_info.getId());
                	HostCollectingTask host_collecting_task = new HostCollectingTask(host_future_map,info);
                	Future future = host_es.scheduleAtFixedRate(host_collecting_task, 1, 2, TimeUnit.MINUTES);
                	host_future_map.put(info.getHostIp(), future);
            	}
            }
            else{
            	jedis.lrem(Constants.COLLECTING_HOST_INFO, 0, value_string);
            }
        	JedisPoolUtils.returnResource(jedis);
            logger.info(res);
        }
        
        else{
        	String ip = test_info.getIp();
        	String port = test_info.getPort();
        	String user_name = test_info.getUserName();
        	String pass = test_info.getPassword();
        	String sid = test_info.getSid();
        	String db_type = "";
        	if(type.equals("1")){
        		db_type = Constants.MYSQL_DB;
        	}
        	else if(type.equals("2")){
        		db_type = Constants.SQL_SERVER;
        	}
        	else{
        		db_type = Constants.ORACLE_DB;
        	}
        	JedisPoolUtils.initPool();
         	Jedis jedis = JedisPoolUtils.getResource();
         	List<String> coll_db_list = jedis.lrange(Constants.COLLECTING_DB_INFO, 0, -1);
         	String key = ip + ":" + port + ":" + db_type + ":" + user_name + ":" +pass;
        	res=testDBCollecting(ip,port,user_name,pass,db_type,sid);
        	if(res==1){
        		if(!coll_db_list.contains(key)){
        			jedis.lpush(Constants.COLLECTING_DB_INFO, key);
        			DatabaseBasicInfo db_basic_info = new DatabaseBasicInfo();
        			db_basic_info.setDbIp(ip);
        			db_basic_info.setDbPassword(pass);
        			db_basic_info.setDbPort(port);
        			db_basic_info.setDbType(db_type);
        			db_basic_info.setDbUsername(user_name);
        			DBCollectingTask db_collecting_task = new DBCollectingTask(db_future_map,db_basic_info);
                	Future future = db_es.scheduleAtFixedRate(db_collecting_task, 1, 2, TimeUnit.MINUTES);
                	host_future_map.put(ip+":"+db_type, future);
        		}
        	}
        	else{
        		jedis.lrem(Constants.COLLECTING_DB_INFO, 0, key);
        	}
        }
        ctx.write(Unpooled.copiedBuffer(res.toString(),CharsetUtil.UTF_8));
    }
    
   
    @Override
    public void channelActive(ChannelHandlerContext ctx){
    	logger.info("--server received connection----");
    }
    
    @Override
    public void channelReadComplete(ChannelHandlerContext ctx) throws Exception {
    	 ctx.writeAndFlush(Unpooled.EMPTY_BUFFER)//4
         .addListener(ChannelFutureListener.CLOSE);
    }


    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) throws  Exception {
        logger.error("server accept message error ", cause);
        ctx.close();
    }


    private int testHostCollecting(String ip, String os) {

        if(!StringUtil.isStrNull(ip) && !StringUtil.isStrNull(os)) {

            logger.info("ip is " + ip);
            logger.info("os is "  + os);
            ScheduledExecutorService es = Executors.newScheduledThreadPool(1);

            ScheduledFuture<Integer> future  = es.schedule(new TestHostMonitorUtil(ip, os), 0, TimeUnit.SECONDS);

            try {
                logger.info("task运行结果 "+future.get());
                int result = future.get();
                if(result == 1) {
                    return 1;

                } else {
                    return 0;
                }
            } catch (InterruptedException e) {
                logger.error("Interruption Exception ", e);
            } catch (ExecutionException e) {
                logger.error("test Host Collecting error", e);
            }
            return 0;

        } else {
            return 0;
        }

    }
    
    
    private int testDBCollecting(String ip, String port, String user_name,String pass ,String type,String sid){
    	if(!StringUtil.isStrNull(ip)&&!StringUtil.isStrNull(port)&&!StringUtil.isStrNull(user_name)&&!StringUtil.isStrNull(pass)&&!StringUtil.isStrNull(type)){
    		logger.info("DB type is"+type);
    		logger.info("DB ip is"+ip);
  
    		if(type.equals(Constants.MYSQL_DB)||type.equals(Constants.ORACLE_DB)||type.equals(Constants.SQL_SERVER)){
    			ScheduledExecutorService es = Executors.newScheduledThreadPool(1);
    			ScheduledFuture<Integer> future  = es.schedule(new TestDBMonitorUtil(type,ip,port,user_name,pass,sid), 0, TimeUnit.SECONDS);
    			
    			try {
					int result = future.get();
					logger.info("db test task result is"+result);
					if(result==1){
						return 1;
					}
					else{
						return 0;
					}
					
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					logger.error(e);
					return 0;
				} catch (ExecutionException e) {
					// TODO Auto-generated catch block
					logger.error(e);
					return 0;
				}
  
    		}
    
    		else{
    			return 0;
    		}
    	}
    	else{
    		return 0;
    	}
    }

}
