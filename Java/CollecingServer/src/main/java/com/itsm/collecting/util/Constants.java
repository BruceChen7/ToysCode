package com.itsm.collecting.util;

/**
 * Created by CM on 2016/7/26.
 */
public class Constants {
    public static int MaxListValueNum = 2 * 1000000;
    public static int ONE_DAY = 3600 * 24;
    public static int ONE_WEEK = 7 * ONE_DAY;

    // 哈希表主机数据
    public static final String HASH_TABLE_NAME = "HOST_DATA_INFO";
    // 所有要采集的主机链表名称列表
    public static final String COLLECTING_HOST_INFO = "COLL_HOST_INFO";

    // 所有要采集的数据库服务器的列表
    public static final String COLLECTING_DB_INFO = "COLL_DB_INFO";

    // 测试是否连接上的channel
    public static final String HOST_SUBSCRIBE_CHANNEL = "TEST_HOST_COLLECTING_CHANNEL";
    // 存放数据库指标数据
    public static final String DB_INDEX_HASH_TABLE = "DATABASE_INDEX_HASH_DATA";


    public static final String MYSQL_DB = "mysql";
    public static final String ORACLE_DB = "oracle";
    public static  final String SQL_SERVER = "sqlserver";


}
