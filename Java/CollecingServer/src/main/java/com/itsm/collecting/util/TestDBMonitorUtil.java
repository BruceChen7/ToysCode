package com.itsm.collecting.util;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.concurrent.Callable;

import org.apache.log4j.Logger;

import com.itsm.collecting.service.MysqlConnectionUtil;
import com.itsm.collecting.service.OracleConnectionUtil;
import com.itsm.collecting.service.SqlServerConnectionUtil;

public class TestDBMonitorUtil implements Callable<Integer> {
	
	private static final Logger logger = Logger.getLogger(TestDBMonitorUtil.class);

	private String db_type;
	private String db_ip;
	private String db_port;
	private String db_user;
	private String db_pass;
	private String db_sid;
	
	public TestDBMonitorUtil(String db_type,String db_ip,String db_port,String db_user,String db_pass,String sid){
		this.db_ip = db_ip;
		this.db_pass = db_pass;
		this.db_port = db_port;
		this.db_type = db_type;
		this.db_user = db_user;
		this.db_sid = db_sid;
	}
	
	@Override
	public Integer call() throws Exception {
		// TODO Auto-generated method stub
		Connection conn = null;
		if(this.db_type.equals(Constants.MYSQL_DB)){
			conn = MysqlConnectionUtil.getInstance().getConnection(db_ip, db_port, null, db_user, db_pass);
			if(conn == null){
				return 0;
			}
			String global_sql = "show global status";
			String variable_sql = "show variables";
			String database_sql = "show databases";
			
			Statement st = conn.createStatement();
			ResultSet rs_1 = st.executeQuery(global_sql);
			ResultSet rs_2 = st.executeQuery(variable_sql);
			ResultSet rs_3 = st.executeQuery(database_sql);
			
			st.close();
			conn.close();
			if(rs_1!=null&&rs_2!=null&&rs_3!=null){
				rs_1.close();
				rs_2.close();
				rs_3.close();
				return 1;
			}
			else{
				rs_1.close();
				rs_2.close();
				rs_3.close();
				return 0;
			}
			
		}
		else if(this.db_type.equals(Constants.ORACLE_DB)){
			conn = OracleConnectionUtil.getInstance().getConnection(db_ip, db_port,db_sid, db_user, db_pass);
			if(conn==null){
				return 0;
			}
			else{
				return 1;
			}
			
		}
		else if(this.db_type.equals(Constants.SQL_SERVER)){
			conn = SqlServerConnectionUtil.getInstance().getConnection(db_ip, db_port, null, db_user, db_pass);
			logger.info(conn);
			if(conn == null){
				return 0;
			}
			else{
				return 1;
			}
		}
		else{
			return 0;
		}
	}

}
