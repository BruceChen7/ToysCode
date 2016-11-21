package com.itsm.collecting.service;

/**
 * Created by CM on 2016/8/25.
 */
public interface IDBCollectingTask {

    // 采集数据库信息接口
    void runCollectJob(String ip, String port, String db_name, String user_name, String pass);
}
