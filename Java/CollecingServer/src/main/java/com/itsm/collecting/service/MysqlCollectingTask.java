package com.itsm.collecting.service;

import com.itsm.collecting.util.Constants;

/**
 * Created by CM on 2016/8/25.
 */
public class MysqlCollectingTask implements  IDBCollectingTask {

    @Override
    public void runCollectJob(String ip, String port, String db_name, String user_name, String pass) {
        MysqlConnectionUtil.getInstance().getMysqlStatus(ip, port, db_name, user_name, pass, Constants.MYSQL_DB);
    }
}
