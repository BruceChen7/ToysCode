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
import com.itsm.collecting.dao.MySqlMonitorInfoMapper;
import com.itsm.collecting.dao.MysqlBasicInfoMapper;
import com.itsm.collecting.model.MySqlMonitorInfo;
import com.itsm.collecting.model.MysqlBasicInfo;
import com.itsm.collecting.util.CollectingIndexName;
import com.itsm.collecting.util.Constants;
import com.itsm.collecting.util.JedisPoolUtils;
import com.itsm.collecting.util.SqlSessionUtil;
import com.itsm.collecting.util.StringUtil;
import com.itsm.collecting.util.TimeTrans;

import redis.clients.jedis.Jedis;

/**
 * Created by CM on 2016/8/11.
 */
public class MysqlConnectionUtil {

    private static MysqlConnectionUtil instance_;
    private static String prefix_url_ = "jdbc:mysql://";
    private static String suffix_url = "?useUnicode=true&characterEncoding=UTF-8&autoReconnect=true";
    private static Logger logger = Logger.getLogger(MysqlConnectionUtil.class);

    public synchronized static MysqlConnectionUtil getInstance() {
        if(instance_ == null) {
            return new MysqlConnectionUtil();
        } else {
            return instance_;
        }
    }


    public Connection getConnection(String ip, String port, String db_name, String user_name, String pass) {
        Connection connection = null;


        try {

            Class.forName("com.mysql.jdbc.Driver");// 动态加载mysql驱动
            logger.info("成功加载MySQL驱动程序");

            String url = constructUrl(ip, port, db_name);

            // 一个Connection代表一个数据库连接
            connection = DriverManager.getConnection(url, user_name, pass);

        } catch (Exception e) {
            logger.error("get connection error ", e);
        }
        return connection;
    }


    public void getMysqlStatus(String ip, String port, String db_name, String user_name, String pass, String db_type) {

        Connection conn = null;
        JedisPoolUtils.initPool();
        Jedis jedis = null;
        SqlSessionFactory factory = SqlSessionUtil.getSqlSession();
        SqlSession s  = factory.openSession(true);

        try {


            conn = getConnection(ip, port, db_name, user_name, pass);
            String sql = "show global status";

            // Get Mysql version
            String variable_sql = "show variables";
            
            String database_instance_sql="show databases";
            
            String database_instance_cpacity="select sum(data_length)+sum(index_length) as db_size from information_schema.tables where table_schema=";

            if(conn != null) {
                //创建SQL语句
                Statement st = conn.createStatement();
                //执行语句，返回结果
                ResultSet rt = st.executeQuery(sql);
                Map<String, String> data = new HashMap<String, String>();
                // 循环取出结果
                while(rt.next()) {
                    // 获取字段
                    String key = rt.getString("Variable_name");
                    String value = rt.getString("Value");
                    data.put(key, value);
                }
                
                // 获取数据库变量值
                Map<String,String> variable_data = new HashMap<String,String>();
                rt = st.executeQuery(variable_sql);
                while(rt.next()) {
                    String key = rt.getString("Variable_name");
                    String value = rt.getString("Value");
                    variable_data.put(key, value);
                }
                
                
                
                // 获取数据库实例名称
                List<String> db_instance_list = new ArrayList<String>();
                rt=st.executeQuery(database_instance_sql);
                while(rt.next()){
                	String db_instance_name_ = rt.getString("Database");
                  	db_instance_list.add(db_instance_name_);
                }
                
                // 获取数据库实例大小
                List<String> db_size_list = new ArrayList<String>();
                for(String db_instance_name:db_instance_list){
                	String temp_sql = database_instance_cpacity+"'"+db_instance_name+"'";
                	rt=st.executeQuery(temp_sql);
                	while(rt.next()){
                		String temp_size=rt.getString("db_size");
                    	db_size_list.add(temp_size);
                	}
                }
                
                
                MySqlMonitorInfo info = new MySqlMonitorInfo();
                String val = parseMysqlStatus(info, data);
      
                
                jedis = JedisPoolUtils.getResource();

                if(jedis != null) {
                    int ts = TimeTrans.getCurrentTimestamp();
                    String list_key = ip + ":" + db_type;



                    if(s == null) {
                        logger.error("can't get sql connection");
                        return;
                    }

                    MySqlMonitorInfoMapper mapper = s.getMapper(MySqlMonitorInfoMapper.class);
                    info.setMonitorTime(ts);
                    val=val+"-Monitor_time:"+ts;
                    int res= mapper.insertSelective(info);

                    if(res == 1) {
                        jedis.lpush(list_key, ""+ts);

                        // 保证redis中的数量合适
                        if (jedis.llen(list_key) >= Constants.MaxListValueNum) {
                            jedis.ltrim(list_key, 0, Constants.MaxListValueNum / 2 - 1);
                        }

                        Map<String, String> db_index_data = new HashMap<String, String>();
                        db_index_data.put(ts + ":" + ip  + ":" + db_type, val);
                        jedis.hmset(Constants.DB_INDEX_HASH_TABLE, db_index_data);
                        jedis.expire(Constants.DB_INDEX_HASH_TABLE, Constants.ONE_WEEK);
                    } else {
                        logger.error("插入数据库失败");
                    }
                    DatabaseBasicInfoMapper data_base_basic_info_mapper = s.getMapper(DatabaseBasicInfoMapper.class);
                    MysqlBasicInfoMapper  mysql_basic_info_mapper = s.getMapper(MysqlBasicInfoMapper.class);
                    Integer database_id = data_base_basic_info_mapper.selectByIpAndType(ip, Constants.MYSQL_DB);
                    MysqlBasicInfo my_basic_info=this.getBasicInfoByMap(variable_data, db_instance_list, db_size_list);
                    logger.info("数据库信息记录id为:"+database_id);
                    MysqlBasicInfo mysql_basic_info = mysql_basic_info_mapper.selectByPrimaryKey(database_id);
                    if(mysql_basic_info == null){
                    	logger.info("数据库信息  does not exits");
                    	my_basic_info.setMysqlId(database_id);
                    	res=mysql_basic_info_mapper.insertSelective(my_basic_info);
                    }
                    else{
                    	logger.info("数据库信息 exits");
                    	my_basic_info.setMysqlId(database_id);
                    	res=mysql_basic_info_mapper.updateByPrimaryKeySelective(my_basic_info);
                    }
                    if(res==0){
                    	logger.error("mysql数据库基本信息更新失败！");
                    }
                    
                    


                } else {
                    logger.error("get Jedis error");
                }


                rt.close();
                st.close();
                conn.close();

            } else {
                logger.error("can't get connection ");
            }
        } catch (Exception e) {
            logger.error("exec sql error ", e);
        } finally {
            if(s != null) {
                s.close();
            }

            JedisPoolUtils.returnResource(jedis);
        }

    }

    // info是一个 in-out 参数
    private String parseMysqlStatus(MySqlMonitorInfo info, Map<String, String> data) {
        String byte_receive = data.get(CollectingIndexName.BYTE_RECEIVE);
        String byte_sent = data.get(CollectingIndexName.BYTE_SENT);
        String table_lock_imme = data.get(CollectingIndexName.TABLE_LOCKS_IMME);
        String table_lock_wait = data.get(CollectingIndexName.TABLE_LOCKS_WAITED);
        String open_connections = data.get(CollectingIndexName.Connections);
        String abort_connections = data.get(CollectingIndexName.ABORTED_CONNECTS);
        String abort_clients = data.get(CollectingIndexName.ABORTED_CLIENTS);
        String thread_cached = data.get(CollectingIndexName.THREADS_CACHED);
        String thread_running = data.get(CollectingIndexName.THREADS_RUNNING);
        String qcache_not_cached = data.get(CollectingIndexName.QCACHE_NOT_CACHED);
        String qcache_inserts = data.get(CollectingIndexName.QCACHE_INSERTS);
        String uptime = data.get(CollectingIndexName.MYSQL_UPTIME);
        int query_not_cached = Integer.parseInt(qcache_not_cached);
        int query_cached = Integer.parseInt(qcache_inserts);
        float cache_rate = (float)query_cached/query_not_cached;


        info.setReceiveByteRate(Integer.parseInt(byte_receive));
        info.setSendByteRate(Integer.parseInt(byte_sent));
        info.setTerminateConnectionNum(Integer.parseInt(abort_connections));
        info.setTerminateClientNum(Integer.parseInt(abort_clients));
        info.setImmediateLockNum(Integer.parseInt(table_lock_imme));
        info.setWaitLockNum(Integer.parseInt(table_lock_imme));
        info.setOpenConnectionNum(Integer.parseInt(open_connections));
        info.setCachedMemoryThreadNum(Integer.parseInt(thread_cached));
        info.setUseThreadNum(Integer.parseInt(thread_running));
        info.setRequestCachedHitRate((int)cache_rate);
        info.setUpTime(Integer.parseInt(uptime));
        


        String val = CollectingIndexName.BYTE_RECEIVE + ":" + byte_receive + "-" + CollectingIndexName.BYTE_SENT + ":" + byte_sent + "-" +
                CollectingIndexName.TABLE_LOCKS_IMME  + ":" + table_lock_imme + "-" + CollectingIndexName.TABLE_LOCKS_WAITED  + ":" + table_lock_wait + "-" +
                CollectingIndexName.Connections + ":" + open_connections + "-" + CollectingIndexName.ABORTED_CONNECTS + ":" + abort_connections + "-" +
                CollectingIndexName.ABORTED_CLIENTS + ":" + abort_clients + "-" + CollectingIndexName.THREADS_CACHED + ":" + thread_cached + "-" +
                CollectingIndexName.THREADS_RUNNING + ":" + thread_running + "-"+CollectingIndexName.MYSQL_UPTIME+":"+uptime+"-"+CollectingIndexName.QCACHE_RATE+":"+(int)cache_rate;


        logger.info(val);
        return val;

    }
    
    private MysqlBasicInfo getBasicInfoByMap(Map<String,String> variable_data,List<String> db_name_list,List<String> db_size_list){
    	MysqlBasicInfo mysql_basic_info = new MysqlBasicInfo();
    	String version = variable_data.get(CollectingIndexName.MYSQL_VERSION);
    	String base_dir = variable_data.get(CollectingIndexName.MYSQL_BASE_DIR);
    	String data_dir = variable_data.get(CollectingIndexName.MYSQL_DATA_DIR);
    	String host_name = variable_data.get(CollectingIndexName.MYSQL_HOST_NAME);
    	String host_os = variable_data.get(CollectingIndexName.MYSQL_HOST_OS);
    	String db_name_string = "";
    	String db_size_string = "";
    	for(String db_name:db_name_list){
    		if(db_name != null){
    			if(db_name_string.equals("")){
    				db_name_string=db_name_string + db_name;
    			}
    			else{
    				db_name_string=db_name_string +","+db_name; 
    			}
    		}
    	}
    	
    	for(String db_size:db_size_list){
    		if(db_size!=null){
    			if(db_size_string.equals("")){
    				db_size_string=db_size_string + db_size;
    			}
    			else{
    				db_size_string=db_size_string +","+db_size;
    			}
    		}
    	}
    	
    	
    	mysql_basic_info.setMysqlBaseDir(base_dir);
    	mysql_basic_info.setMysqlDataDir(data_dir);
    	mysql_basic_info.setMysqlHostName(host_name);
    	mysql_basic_info.setMysqlHostOs(host_os);
    	mysql_basic_info.setMysqlVersion(version);
    	mysql_basic_info.setMysqlDbNameList(db_name_string);
    	mysql_basic_info.setMysqlDbSizeList(db_size_string);
    	
    	return mysql_basic_info;
    }
    
    
    

    private String constructUrl(String ip, String port, String db_name) {

        if(StringUtil.isStrNull(port)) {
           port = "3306";
        }

        String url = "";
        if(!StringUtil.isStrNull(db_name)) {
           url =  prefix_url_ + ip +  ":" + port +"/" + db_name + suffix_url;
        } else {
            url =  prefix_url_ + ip +  ":" + port +"/" + suffix_url;
        }
        logger.info("url is " + url);
        return url;
    }
}
