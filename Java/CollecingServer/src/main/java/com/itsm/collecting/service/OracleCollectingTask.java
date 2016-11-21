package com.itsm.collecting.service;

import com.itsm.collecting.util.Constants;

public class OracleCollectingTask implements IDBCollectingTask {

	@Override
	public void runCollectJob(String ip, String port, String db_name, String user_name, String pass) {
		// TODO Auto-generated method stub
		OracleConnectionUtil.getInstance().getOracleStatus(ip, port, db_name, user_name, pass, Constants.ORACLE_DB);
	}

}
