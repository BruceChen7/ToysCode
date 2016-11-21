package com.itsm.collecting.service;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.log4j.Logger;

import com.itsm.collecting.dao.DatabaseBasicInfoMapper;
import com.itsm.collecting.dao.OracleBasicInfoMapper;
import com.itsm.collecting.dao.OracleMonitorInfoMapper;
import com.itsm.collecting.model.OracleBasicInfo;
import com.itsm.collecting.model.OracleMonitorInfo;
import com.itsm.collecting.util.Constants;
import com.itsm.collecting.util.JedisPoolUtils;
import com.itsm.collecting.util.SqlSessionUtil;
import com.itsm.collecting.util.TimeTrans;

import io.netty.util.internal.StringUtil;
import redis.clients.jedis.Jedis;

public class OracleConnectionUtil {
	
	private static OracleConnectionUtil instance_;
	private static String prefix_url = "JDBC:oracle:thin:@";
	private static Logger logger = Logger.getLogger(OracleConnectionUtil.class);
	
	public synchronized static OracleConnectionUtil getInstance(){
		if(instance_ == null){
			return new OracleConnectionUtil();
		}else{
			return instance_;
		}
	}
	
	public Connection getConnection(String ip,String port, String db_name, String user_name, String pass){
		Connection connection = null;
		
		try{
			
			Class.forName("oracle.jdbc.driver.OracleDriver");
			logger.info("成功注册oracle驱动");
			String url = ConstructUrl(ip,port,db_name);
			logger.info("oracle connect url is "+url);
			logger.info("oracle user name is "+user_name);
			logger.info("oracle pass is "+pass);
			connection = DriverManager.getConnection(url, user_name, pass);
			
		} catch(Exception e){
			logger.error("oracle get connection from "+ip+" error" +e);
		}
		return connection;
	}
	
	
	
	
	public void getOracleStatus(String ip, String port, String db_name ,String user_name, String pass , String db_type){
		//初始化变量
		Connection conn =null;
		SqlSessionFactory sql_session_factory = SqlSessionUtil.getSqlSession();
		SqlSession sql_session = sql_session_factory.openSession(true);
		JedisPoolUtils.initPool();
		Jedis jedis=null;
		
		
		//指标查询sql语句
		//数据库基本信息
		String version_sql = "select * from v$version";
		String startup_time_sql = "select startup_time from v$instance";
		String user_num_sql = "select count(distinct username)as user_count from v$session";
		String database_info_sql = "select created,log_mode,open_mode from v$database";
		String database_size_sql = "select round(sum(bytes)/1024/1024) as db_size from dba_data_files";
		String database_block_size = "select min(block_size) as block_size from v$datafile";
		
		//表空间明细
		
		String tablespace_info_sql = "select a.tablespace_name,a.status from dba_tablespaces a";
		String tablespace_detail_sql_front = "select count(a.file_id) as file_count,sum(a.bytes) as file_byte"
				+ ",sum(a.blocks) as file_blocks,sum(b.bytes) as free_file_byte,sum(b.blocks) as free_file_blocks,"
				+ "sum(c.phyrds) as read_num,sum(c.phywrts) as write_num,round(avg(c.readtim*1.0/100/c.phyrds),3) as avg_read_time,"
				+ "round(avg(c.writetim*1.0/100/c.phywrts),3) as avg_write_time "
				+ "from dba_data_files a, dba_free_space b, v$filestat c "
				+ "where c.file#=a.file_id and a.tablespace_name=";
		String tablespace_detail_sql_next="and b.tablespace_name=";
		
		
		
		//SGA明细
		String sga_buffer_cache_sql = "select bytes from v$sgastat where name='buffer_cache'";
		String sga_shared_pool_sql = "select count(bytes)as pool_size from v$sgastat where pool='shared pool'";
		String sga_log_buffer_sql = "select bytes from v$sgastat where name='log_buffer'";
		String sga_size_sql = "select sum(value) as sga_size from v$sga";
		
		String sga_data_dictionary_cache_sql = "select sum(gets) as data_dictionary_cache,sum(gets-getmisses-usage-fixed)*1.0/sum(gets) as data_dictionary_cache_hit_rate  from v$rowcache";	
		String sga_library_cache_sql="select sum(pins) as sql_cache_size , sum(gethits)/sum(gets) as sql_cache_hit_rate from v$librarycache";
		
		//数据文件明细
		String data_file_info_sql = "select a.file_name,a.tablespace_name,a.bytes,a.online_status,b.phyrds as read_num,"
				+ "b.phywrts as write_num,round(b.readtim*1.0/100/b.phyrds,3) as avg_read_time,round(b.writetim*1.0/100/b.phywrts,3) as avg_write_time "
				+ "from dba_data_files a,v$filestat b "
				+ "where a.file_id=b.FILE#";
		
		//会话明细
		
		String session_info_sql = "select a.sID,a.STATUS,a.OSUSER,a.USERNAME,a.LOGON_TIME from v$session a where a.audsid!=0";
		String session_stat_sql="select b.name,a.value from v$sesstat a,v$statname b where a.statistic#=b.statistic# and a.sid=";
		
		//回退段明细
		String seg_detail_sql = "select a.segment_name,a.tablespace_name,a.status,a.initial_extent,a.next_extent,a.min_extents,a.max_extents,"
				+ "round(b.gets*1.0/(b.gets+b.waits)) as hit_rate, b.HWMSIZE,b.extends,b.shrinks,b.wraps "
				+ "from dba_rollback_segs a, v$rollstat b "
				+ "where a.segment_id=b.USN";
		
		
		
		
		//指标查询,属性设置开始
		conn = this.getConnection(ip, port, db_name, user_name, pass);
		OracleBasicInfo oracle_basic_info = new OracleBasicInfo();
		OracleMonitorInfo oracle_monitor_info = new OracleMonitorInfo();
		try{
			if(conn!=null){
				Statement st = conn.createStatement();
				ResultSet rs =null;
				
				int current_ts = TimeTrans.getCurrentTimestamp();
				oracle_monitor_info.setMonitorTime(current_ts);

				//数据库基本信息
				rs=st.executeQuery(version_sql);
				if(rs.next()){
					oracle_basic_info.setOracleVersion(rs.getString("BANNER"));
				}
				else{
					oracle_basic_info.setOracleVersion("");
				}
				rs=st.executeQuery(startup_time_sql);
				if(rs.next()){
					String start_time = rs.getString("STARTUP_TIME");
					int start_time_int = TimeTrans.DateTimeToTimestamp(start_time);
					oracle_basic_info.setOracleStartTime(start_time_int);
				}
				else{
					oracle_basic_info.setOracleStartTime(0);
				}
				rs=st.executeQuery(user_num_sql);
				if(rs.next()){
					String user_num = rs.getString("USER_COUNT");
				}
				else{
					
				}
				rs=st.executeQuery(database_info_sql);
				if(rs.next()){
					String create_time = rs.getString("CREATED");
					String log_mode = rs.getString("LOG_MODE");
					String open_mode = rs.getString("OPEN_MODE");
					
					
					oracle_basic_info.setOracleFoundTime(TimeTrans.DateTimeToTimestamp(create_time));
					oracle_basic_info.setOracleLogType(log_mode);
					oracle_basic_info.setOracleOpenType(open_mode);
				}
				rs=st.executeQuery(database_size_sql);
				if(rs.next()){
					String db_size = rs.getString("db_size");					
					oracle_basic_info.setOracleSize(Integer.parseInt(db_size));
				}
				rs=st.executeQuery(database_block_size);
				if(rs.next()){
					String block_size = rs.getString("block_size");
					oracle_basic_info.setOracleBlockSize(Integer.parseInt(block_size));
				}
				
				logger.info("oracle 数据库基本信息结束");
				
				//表空间信息
				
				List<String> tablespace_name_list = new ArrayList<String>();
				List<String> tablespace_status_list = new ArrayList<String>();
				rs=st.executeQuery(tablespace_info_sql);
				while(rs.next()){
					tablespace_name_list.add(rs.getString("TABLESPACE_NAME"));
					tablespace_status_list.add(rs.getString("STATUS"));
				}
				if(tablespace_name_list.size()!=0){
					List<String> file_count_list=new ArrayList<String>();
					List<String> file_byte_list=new ArrayList<String>();
					List<String> file_blocks_list=new ArrayList<String>();
					List<String> free_file_byte_list=new ArrayList<String>();
					List<String> free_file_blocks_list=new ArrayList<String>();
					List<String> read_num_list=new ArrayList<String>();
					List<String> write_num_list=new ArrayList<String>();
					List<String> avg_read_time_list=new ArrayList<String>();
					List<String> avg_write_time_list=new ArrayList<String>();
					for(String tablespace_name:tablespace_name_list){
				
						logger.info(tablespace_detail_sql_front+"'"+tablespace_name+"'"+tablespace_detail_sql_next+"'"+tablespace_name+"'");
						rs=st.executeQuery(tablespace_detail_sql_front+"'"+tablespace_name+"'"+tablespace_detail_sql_next+"'"+tablespace_name+"'");
					    if(rs.next()){
					    	file_count_list.add(rs.getString("FILE_COUNT"));
							file_byte_list.add(rs.getString("FILE_BYTE"));
							file_blocks_list.add(rs.getString("FILE_BLOCKS"));
							free_file_byte_list.add(rs.getString("FREE_FILE_BYTE"));
							free_file_blocks_list.add(rs.getString("FREE_FILE_BLOCKS"));
							read_num_list.add(rs.getString("READ_NUM"));
							write_num_list.add(rs.getString("WRITE_NUM"));
							avg_read_time_list.add(rs.getString("AVG_READ_TIME"));
							avg_write_time_list.add(rs.getString("AVG_WRITE_TIME"));
					    }
						
					}
					oracle_basic_info.setTablesapceBlockNum(this.DataArrayToString(file_blocks_list));
					oracle_basic_info.setTablespaceByteNum(this.DataArrayToString(file_byte_list));
					oracle_basic_info.setTablespaceFileNum(this.DataArrayToString(file_count_list));
					oracle_basic_info.setTablespaceFreeBlock(this.DataArrayToString(free_file_blocks_list));
					oracle_basic_info.setTablespaceFreeByte(this.DataArrayToString(free_file_byte_list));
					oracle_basic_info.setTablespaceName(this.DataArrayToString(tablespace_name_list));
					oracle_basic_info.setTablespaceReadNum(this.DataArrayToString(read_num_list));
					oracle_basic_info.setTablespaceReadTime(this.DataArrayToString(avg_read_time_list));
					oracle_basic_info.setTablespaceStatus(this.DataArrayToString(tablespace_status_list));
					oracle_basic_info.setTablespaceWriteNum(this.DataArrayToString(write_num_list));
					oracle_basic_info.setTablespaceWriteTime(this.DataArrayToString(avg_write_time_list));
				}
				
				logger.info("oracle 数据库表空间信息结束");
				
				//SGA明细
				rs=st.executeQuery(sga_buffer_cache_sql);
				if(rs.next()){
					String bytes=rs.getString("BYTES");
					oracle_monitor_info.setSgaBufferCacheSize(Integer.parseInt(bytes));
				}
				rs=st.executeQuery(sga_shared_pool_sql);
				if(rs.next()){
					String pool_size=rs.getString("pool_size");
					oracle_monitor_info.setSgaSharedPoolSize(Integer.parseInt(pool_size));
				}
				rs=st.executeQuery(sga_log_buffer_sql);
				if(rs.next()){
					String log_buffer_size = rs.getString("BYTES");
					oracle_monitor_info.setSgaLogBufferSize(Integer.parseInt(log_buffer_size));
				}
				rs=st.executeQuery(sga_size_sql);
				if(rs.next()){
					String sga_size=rs.getString("sga_size");
					oracle_monitor_info.setSgaSize(Integer.parseInt(sga_size));
				}
				rs=st.executeQuery(sga_data_dictionary_cache_sql);
				if(rs.next()){
					String sga_dictionary_cache=rs.getString("data_dictionary_cache");
					String sga_dictionary_cache_hit_rate=rs.getString("data_dictionary_cache_hit_rate");
					Double sga_dic_hit_rate = Double.parseDouble(sga_dictionary_cache_hit_rate)*100;
					oracle_monitor_info.setSgaDictionaryCacheSize(Integer.parseInt(sga_dictionary_cache));
					oracle_monitor_info.setSgaDictionaryHitrate(sga_dic_hit_rate.intValue());
				}
				rs=st.executeQuery(sga_library_cache_sql);
				if(rs.next()){
					String sga_sql_cache_size=rs.getString("sql_cache_size");
					String sga_sql_cache_hit_rate=rs.getString("sql_cache_hit_rate");
					Double sga_cache_hit_rate = Double.parseDouble(sga_sql_cache_hit_rate);
					oracle_monitor_info.setSgaLibraryCacheSize(Integer.parseInt(sga_sql_cache_size));
					oracle_monitor_info.setSgaLibraryHitrate(sga_cache_hit_rate.intValue());
				}
				
				logger.info("SGA 明细结束");
				
				//数据文件明细
				rs=st.executeQuery(data_file_info_sql);
				while(rs.next()){
					List<String> data_file_name_list = new ArrayList<String>();
					List<String> data_tablespace_name_list = new ArrayList<String>();
					List<String> data_bytes_list = new ArrayList<String>();
					List<String> data_online_status_list = new ArrayList<String>();
					List<String> data_read_num = new ArrayList<String>();
					List<String> data_write_num = new ArrayList<String>();
					List<String> avg_read_time = new ArrayList<String>();
					List<String> avg_write_time = new ArrayList<String>();
					
					data_file_name_list.add(rs.getString("FILE_NAME"));
					data_tablespace_name_list.add(rs.getString("TABLESPACE_NAME"));
					data_bytes_list.add(rs.getString("BYTES"));
					data_online_status_list.add(rs.getString("ONLINE_STATUS"));
					data_read_num.add(rs.getString("READ_NUM"));
					data_write_num.add(rs.getString("WRITE_NUM"));
					avg_read_time.add(rs.getString("AVG_READ_TIME"));
					avg_write_time.add(rs.getString("AVG_WRITE_TIME"));
					
					
					oracle_basic_info.setDataFileAvgReadTime(this.DataArrayToString(avg_read_time));
					oracle_basic_info.setDataFileAvgWriteTime(this.DataArrayToString(avg_write_time));
					oracle_basic_info.setDataFileCreateSize(this.DataArrayToString(data_bytes_list));
					oracle_basic_info.setDataFileName(this.DataArrayToString(data_file_name_list));
					oracle_basic_info.setDataFileReadNum(this.DataArrayToString(data_read_num));
					oracle_basic_info.setDataFileStatus(this.DataArrayToString(data_online_status_list));
					oracle_basic_info.setDataFileTablespace(this.DataArrayToString(data_tablespace_name_list));
					oracle_basic_info.setDataFileWriteNum(this.DataArrayToString(data_write_num));
					
					
				}
				
				logger.info("数据文件 明细结束");
				
				//会话明细
				rs=st.executeQuery(session_info_sql);
				List<String> session_sid_list = new ArrayList<String>();
				List<String> session_status_list = new ArrayList<String>();
				List<String> session_outuser_list = new ArrayList<String>();
				List<String> session_user_list = new ArrayList<String>();
				List<String> session_start_time = new ArrayList<String>();
			
				while(rs.next()){
					session_sid_list.add(rs.getString("SID"));
					session_status_list.add(rs.getString("STATUS"));
					session_outuser_list.add(rs.getString("OSUSER"));
					session_user_list.add(rs.getString("USERNAME"));
					session_start_time.add(rs.getString("LOGON_TIME"));					
				}
				
				if(session_sid_list.size()!=0){
					List<String> opened_cursors_currrent = new ArrayList<String>();
					List<String> user_commits_list=new ArrayList<String>();
					List<String> session_logical_reads_list = new ArrayList<String>();
					List<String> cpu_used_list = new ArrayList<String>();
					List<String> session_during_time_list = new ArrayList<String>();
					
					
					int i=0;
					for(String session_sid:session_sid_list){
						logger.info(session_sid);
						rs=st.executeQuery(session_stat_sql+Integer.parseInt(session_sid));
						Map<String,Object> session_stat_map = new HashMap<String,Object>();
						while(rs.next()){
							session_stat_map.put(rs.getString("NAME"), rs.getString("VALUE"));
						}
						opened_cursors_currrent.add(session_stat_map.get("opened cursors current").toString());
						
						logger.info("seesion 1");
						user_commits_list.add(session_stat_map.get("user commits").toString());
						logger.info("session 2");
						session_logical_reads_list.add(session_stat_map.get("session logical reads").toString());
						logger.info("session 3");
						cpu_used_list.add(session_stat_map.get("CPU used by this session").toString());
						logger.info("session 4");
						Integer session_during_time = current_ts - TimeTrans.DateTimeToTimestamp(session_start_time.get(i));
						session_during_time_list.add(session_during_time.toString());
						i++;
						
						
					}
					
					oracle_basic_info.setSessionCpuUseTime(this.DataArrayToString(cpu_used_list));
					oracle_basic_info.setSessionCursorNum(this.DataArrayToString(opened_cursors_currrent));
					oracle_basic_info.setSessionDbUserName(this.DataArrayToString(session_user_list));
					oracle_basic_info.setSessionId(this.DataArrayToString(session_sid_list));
					oracle_basic_info.setSessionLogTime(this.DataArrayToString(session_during_time_list));
					oracle_basic_info.setSessionLogireadNum(this.DataArrayToString(session_logical_reads_list));
					oracle_basic_info.setSessionOutUserName(this.DataArrayToString(session_outuser_list));
					oracle_basic_info.setSessionStatus(this.DataArrayToString(session_status_list));
					oracle_basic_info.setSessionSubmitNum(this.DataArrayToString(user_commits_list));
				}
				
				logger.info("会话明细结束");
				
				//回退段明细
				logger.info(seg_detail_sql);
				rs=st.executeQuery(seg_detail_sql);
				List<String> segment_name_list = new ArrayList<String>();
				List<String> seg_tablespace_name_list = new ArrayList<String>();
				List<String> seg_status_list = new ArrayList<String>();
				List<String> seg_initial_extent_list = new ArrayList<String>();
				List<String> seg_next_extent_list = new ArrayList<String>();
				List<String> seg_min_extent_list = new ArrayList<String>();
				List<String> seg_max_extent_list = new ArrayList<String>();
				List<String> seg_hit_rate_list = new ArrayList<String>();
				List<String> seg_hwmsize_list = new ArrayList<String>();
				List<String> seg_extends_list = new ArrayList<String>();
				List<String> seg_shrinks_list = new ArrayList<String>();
				List<String> seg_wraps_list = new ArrayList<String>();
				
				logger.info("segment sql excute successfully");
				while(rs.next()){				
					
					segment_name_list.add(rs.getString("SEGMENT_NAME"));
					seg_tablespace_name_list.add(rs.getString("TABLESPACE_NAME"));
					seg_status_list.add(rs.getString("STATUS"));
					seg_initial_extent_list.add(rs.getString("INITIAL_EXTENT"));
					seg_next_extent_list.add(rs.getString("NEXT_EXTENT"));
					seg_min_extent_list.add(rs.getString("MIN_EXTENTS"));
					seg_max_extent_list.add(rs.getString("MAX_EXTENTS"));
					seg_hit_rate_list.add(rs.getString("HIT_RATE"));
					seg_hwmsize_list.add(rs.getString("HWMSIZE"));
					seg_extends_list.add(rs.getString("EXTENDS"));
					seg_shrinks_list.add(rs.getString("SHRINKS"));
					seg_wraps_list.add(rs.getString("WRAPS"));
										
				}
				
				oracle_basic_info.setRollbackSegExtends(this.DataArrayToString(seg_extends_list));
				oracle_basic_info.setRollbackSegHitRate(this.DataArrayToString(seg_hit_rate_list));
				oracle_basic_info.setRollbackSegHwmsize(this.DataArrayToString(seg_hwmsize_list));
				oracle_basic_info.setRollbackSegInitSize(this.DataArrayToString(seg_initial_extent_list));
				oracle_basic_info.setRollbackSegMaxExtent(this.DataArrayToString(seg_max_extent_list));
				oracle_basic_info.setRollbackSegMinExtent(this.DataArrayToString(seg_min_extent_list));
				oracle_basic_info.setRollbackSegName(this.DataArrayToString(segment_name_list));
				oracle_basic_info.setRollbackSegNextSize(this.DataArrayToString(seg_next_extent_list));
				oracle_basic_info.setRollbackSegShrinks(this.DataArrayToString(seg_shrinks_list));
				oracle_basic_info.setRollbackSegStatus(this.DataArrayToString(seg_status_list));
				oracle_basic_info.setRollbackSegTablespace(this.DataArrayToString(seg_tablespace_name_list));
				oracle_basic_info.setRollbackSegWraps(this.DataArrayToString(seg_wraps_list));
				
				logger.info("回退段 明细结束");
				
				//存储指标数据开始
				jedis=JedisPoolUtils.getResource();
				if(jedis!=null){
					String db_key=ip+":"+Constants.ORACLE_DB;
					String db_monitor_key=current_ts+":"+db_key;
					jedis.lpush(db_key, ""+current_ts);
					jedis.hset(Constants.DB_INDEX_HASH_TABLE,db_monitor_key,oracle_monitor_info.ObjectToString());
					if(sql_session!=null){
						DatabaseBasicInfoMapper db_basic_info_mapper = sql_session.getMapper(DatabaseBasicInfoMapper.class);
						OracleBasicInfoMapper  oracle_basic_info_mapper = sql_session.getMapper(OracleBasicInfoMapper.class);
						OracleMonitorInfoMapper oracle_monitor_info_mapper = sql_session.getMapper(OracleMonitorInfoMapper.class);
						
						Integer db_id = db_basic_info_mapper.selectByIpAndType(ip, Constants.ORACLE_DB);
						oracle_monitor_info.setDbId(db_id);
						oracle_monitor_info.setMonitorTime(current_ts);
						int res = oracle_monitor_info_mapper.insertSelective(oracle_monitor_info);
						if(res==1){
							OracleBasicInfo oracle_basic_info_temp =oracle_basic_info_mapper.selectByPrimaryKey(db_id);
							if(oracle_basic_info_temp!=null){
								oracle_basic_info.setOracleId(db_id);
								oracle_basic_info_mapper.updateByPrimaryKeySelective(oracle_basic_info);
							}
							else{
								oracle_basic_info.setOracleId(db_id);
								oracle_basic_info_mapper.insertSelective(oracle_basic_info);
							}
						}
						else{
							logger.error("更新数据库监控信息失败");
						}
						
						
					}
					else{
						logger.error("can not get sql session from database");
					}
				}
				else{
					logger.error("can not get jedis connection !");
					return;
				}
						
				st.close();
				conn.close();
			}
			else{
				logger.error("can not get connection from "+ip+":"+port+" "+db_name);
			}
		}catch(Exception e){
			logger.error(e);
		}finally{
			JedisPoolUtils.returnResource(jedis);
		}
		
	}
	
	
	
	
	
	public String ConstructUrl(String ip,String port,String sid){
		String url ="";
		if (StringUtil.isNullOrEmpty(port)){
			port = "1521";
		}
		if (StringUtil.isNullOrEmpty(sid)){
			sid="orcl";
		}
		
		url = prefix_url + ip + ":" + port+ ":" + sid;
		
		return url;
	}
	
	private String DataArrayToString(List<String> data_list){
		if(data_list==null){
			return "";
		}
		String data_string = "";
		for(String data:data_list){
			data_string=data_string+","+data;
		}
		
		data_string = data_string.substring(1);
		return data_string;
	}
}
