package com.itsm.collecting.service;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.log4j.Logger;

import com.itsm.collecting.dao.DatabaseBasicInfoMapper;
import com.itsm.collecting.dao.MssqlBasicInfoMapper;
import com.itsm.collecting.dao.MssqlMonitorInfoMapper;
import com.itsm.collecting.model.DatabaseBasicInfo;
import com.itsm.collecting.model.MssqlBasicInfo;
import com.itsm.collecting.model.MssqlMonitorInfo;
import com.itsm.collecting.util.Constants;
import com.itsm.collecting.util.JedisPoolUtils;
import com.itsm.collecting.util.SqlSessionUtil;
import com.itsm.collecting.util.StringUtil;
import com.itsm.collecting.util.TimeTrans;
import com.microsoft.sqlserver.jdbc.SQLServerDriver;

import redis.clients.jedis.Jedis;


public class SqlServerConnectionUtil {
	private static SqlServerConnectionUtil instance_;
	private static String prefix_url = "jdbc:sqlserver://";
	private static Logger logger = Logger.getLogger(SqlServerConnectionUtil.class);
	
	
	public synchronized static SqlServerConnectionUtil getInstance() {
		if(instance_ == null){
			return new SqlServerConnectionUtil();
		}else{
			return instance_;
		}
	}
	 
	public Connection getConnection(String ip, String port,String db_name, String user_name, String pass) {
		Connection connection = null;
		
		try{
			
			Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
			logger.info("成功加载SqlServer驱动程序");
			
			String url = constructUrl(ip, port, db_name);
			connection = DriverManager.getConnection(url, user_name, pass);
			return connection;
						
		}catch(Exception e){
			logger.error("get connection from "+ ip +" db error "+e);
		}
		
		return connection;
	}
	
	
	public void getSqlServerStatus(String ip, String port,String db_name,String user_name, String pass , String db_type){
		
		Connection conn = null;
		JedisPoolUtils.initPool();
		Jedis jedis = null;
		SqlSessionFactory factory = SqlSessionUtil.getSqlSession();
		SqlSession s = factory.openSession(true);
		
		try{
			
			logger.info("sqlserver ip is:"+ip);
			
			conn=this.getConnection(ip, port, db_name, user_name, pass);
			// 数据库基本信息
			String db_version_sql = "select @@VERSION as 'version'"; //数据库版本
			String db_host_name_sql = "select @@SERVERNAME as 'server_name'"; // 主机名
//			String db_host_os_sql = "select windows_release from sys.dm_os_windows_info";//主机操作系统
			//内存使用信息
			String total_memory_sql = "select physical_memory_in_use_kb from sys.dm_os_process_memory"; // 所使用的动态内存
			
			
			//缓冲管理器统计
			String hit_rate_sql = "select sum(hits_count)*1.0/(sum(hits_count)+sum(misses_count)) as 'hit_rate' from sys.dm_os_memory_cache_hash_tables"; //缓存击中率
			
			//连接统计
			String active_login_count_sql = "select count(*) as 'active_login_count' from sys.syslogins";
			
			//锁明细
			
			//Latch 明细
			String latch_wait_count_sql = "select sum(waiting_requests_count) as 'wait_latch_count' from sys.dm_os_latch_stats"; // latch等待总数
			
			String avg_latch_wait_time_sql = "select sum(wait_time_ms)*1.0/sum(waiting_requests_count) as 'avg_latch_wait_time' from sys.dm_os_latch_stats";//平均Latch等待时间
			
			//数据库 明细
			String data_file_sql = "select sum(size) as 'file_size' from sys.database_files where type_desc = 'ROWS'";
			
			String log_file_sql = "select sum(size) as 'file_size' from sys.database_files where type_desc = 'LOG'";
			
			//数据库启动时间
			String start_time_sql = "select sqlserver_start_time from sys.dm_os_sys_info";
			
			if(conn !=null){
				
				DatabaseBasicInfoMapper data_base_basic_info_mapper = s.getMapper(DatabaseBasicInfoMapper.class);
				
				MssqlBasicInfo sqlserver_basic_info=new MssqlBasicInfo();
				MssqlMonitorInfo  sqlserver_monitor_info = new MssqlMonitorInfo();
				Integer data_base_id = data_base_basic_info_mapper.selectByIpAndType(ip, Constants.SQL_SERVER);
				int current_ts = TimeTrans.getCurrentTimestamp();
				
				logger.info("current ts is"+current_ts);

				
				Statement st = conn.createStatement();
				ResultSet rt;
				
				//查询数据库基本信息
				rt = st.executeQuery(db_version_sql);
				String db_version="";
				while(rt.next()){
					db_version= rt.getString("version");
				} 
				logger.info("sqlserver version is"+db_version);
				
				rt= st.executeQuery(db_host_name_sql);
				String db_host_name = "";
				while(rt.next()){
					db_host_name=rt.getString("server_name");
				}
				logger.info("sqlserver version is"+db_host_name);
			
//				rt = st.executeQuery(db_host_os_sql);
//				String windows_release = "";
//				while(rt.next()){
//					windows_release=rt.getString("windows_release");
//				}
				sqlserver_basic_info.setMssqlHostName(db_host_name);
//				sqlserver_basic_info.setMssqlHostOs(windows_release);
				sqlserver_basic_info.setMssqlVersion(db_version);
				
				
				//数据库服务器开启时间
				rt = st.executeQuery(start_time_sql);
				String sql_start_time="";
				while(rt.next()){
					sql_start_time = rt.getString("sqlserver_start_time");
				}
				String time_fomat = sql_start_time.substring(0, sql_start_time.lastIndexOf("."));
				int sql_start_ts = TimeTrans.DateTimeToTimestamp(time_fomat);
				
				
				//查询内存使用
				rt = st.executeQuery(total_memory_sql);
				String total_memory_in_use ="";
				while(rt.next()){
					total_memory_in_use= rt.getString("physical_memory_in_use_kb");
				}
				sqlserver_monitor_info.setTotalMemory(Integer.parseInt(total_memory_in_use));
				
				//缓存管理器统计
				rt = st.executeQuery(hit_rate_sql);
				String hit_rate="";
				while(rt.next()){
					hit_rate = rt.getString("hit_rate");
				}
				Double hit_rate_double = Double.parseDouble(hit_rate)*100;	
				sqlserver_monitor_info.setCacheHitRate(hit_rate_double.intValue());
				
				//连接统计查询
				rt = st.executeQuery(active_login_count_sql);
				String active_count = "";
				while(rt.next()){
					active_count=rt.getString("active_login_count");
				}
				sqlserver_monitor_info.setConnectionNum(Integer.parseInt(active_count));
				logger.info("sqlserver active_count is"+active_count);
				
				//锁明细
				
				//Latch 明细
				rt = st.executeQuery(latch_wait_count_sql);
				String latch_wait_count = "";
				while(rt.next()){
					latch_wait_count=rt.getString("wait_latch_count");
				}
				int latch_wait_count_int = Integer.parseInt(latch_wait_count);
				Double latch_rate = (double)latch_wait_count_int/(current_ts-sql_start_ts)/60*100;
				sqlserver_monitor_info.setLatchWaitNumPerMinute(latch_rate.intValue());
				
				
				rt = st.executeQuery(avg_latch_wait_time_sql);
				String avg_latch_wait_time = "";
				while(rt.next()){
					avg_latch_wait_time =rt.getString("avg_latch_wait_time");
				}
				Double avg_latch_time = Double.parseDouble(avg_latch_wait_time);
				sqlserver_monitor_info.setAvgLatchWaitTime(avg_latch_time.intValue());
				
				
				//数据库明细
				rt = st.executeQuery(data_file_sql);
				String data_file_size = "";
				while(rt.next()){
					data_file_size=rt.getString("file_size");
				}
				sqlserver_monitor_info.setDataFileSize(Integer.parseInt(data_file_size));
				logger.info("sqlserver data file size is monitor_info");
				
				rt = st.executeQuery(log_file_sql);
				String log_file_size = "";
				while(rt.next()){
					log_file_size=rt.getString("file_size");
				}
				sqlserver_monitor_info.setLogFileSize(Integer.parseInt(log_file_size));
				
				
				
				//数据处理部分
				jedis=JedisPoolUtils.getResource();
				if(jedis!=null){
					MssqlBasicInfoMapper sqlserver_basic_info_mapper = s.getMapper(MssqlBasicInfoMapper.class);
					MssqlMonitorInfoMapper sqlserver_monitor_info_mapper = s.getMapper(MssqlMonitorInfoMapper.class);
					String time_list_key = ip+ ":"+Constants.SQL_SERVER;
					String hash_data_key = current_ts + ":" + time_list_key;
					
					sqlserver_monitor_info.setMonitorTime(current_ts);
					sqlserver_monitor_info.setDbId(data_base_id);
					int res = sqlserver_monitor_info_mapper.insertSelective(sqlserver_monitor_info);
					if(res==1){
						jedis.hset(Constants.DB_INDEX_HASH_TABLE,hash_data_key,sqlserver_monitor_info.ObjectToString());
						jedis.lpush(time_list_key,""+current_ts);
					}else{
						logger.error("监控数据插入数据库失败！");
					}
					
					MssqlBasicInfo sqlserver_basic_info_temp = sqlserver_basic_info_mapper.selectByPrimaryKey(data_base_id);
					if(sqlserver_basic_info_temp==null){
						logger.info("数据库信息 does not exits");
						sqlserver_basic_info.setMssqlId(data_base_id);
						res = sqlserver_basic_info_mapper.insertSelective(sqlserver_basic_info);
					}
					else{
						logger.info("数据库信息 exits");
						sqlserver_basic_info.setMssqlId(data_base_id);
						res = sqlserver_basic_info_mapper.updateByPrimaryKeySelective(sqlserver_basic_info);
					}
					if(res==0){
						logger.error(ip+" "+Constants.SQL_SERVER+"数据库基本信息更新失败!");
					}
				}
				else{
					logger.error("can not get Redis connection!");
				}
				rt.close();
				st.close();
				conn.close();
			}
			else{
				logger.error("can not connect"+ip + " "+db_type);
				return;
			}
			
		}catch(Exception e){
			logger.error(e);
		}finally{
			if(s !=null){
				s.close();
			}			
			JedisPoolUtils.returnResource(jedis);
		}
	}
	
	private String constructUrl(String ip, String port, String db_name) {
		if(StringUtil.isStrNull(port)){
			port = "1433";
		}
		
		String url = "";
		if(StringUtil.isStrNull(db_name)){
			url = prefix_url + ip + ":" + port + ";";
		} else {
			url = prefix_url + ip + ":" + port + ";"+"DatabaseName=" + db_name;
		}
		
		logger.info("url is" + url);
		return url;
	}
}
