package com.itsm.collecting.service;

import com.itsm.collecting.util.Constants;

public class SqlServerCollectingTask implements IDBCollectingTask {

	@Override
	public void runCollectJob(String ip, String port, String db_name, String user_name, String pass) {
		
		// TODO Auto-generated method stub
		SqlServerConnectionUtil.getInstance().getSqlServerStatus(ip, port, db_name, user_name, pass, Constants.SQL_SERVER);
	}

}
