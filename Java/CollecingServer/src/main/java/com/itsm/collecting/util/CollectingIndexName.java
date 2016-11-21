package com.itsm.collecting.util;

/**
 * Created by CM on 2016/7/25.
 */
public class CollectingIndexName {
    public static final String cpuUsage = "cpu_usage_percent";
    public static final String memorySize = "memory_size";
    public static final String usedMemorySize = "used_memory_size";
    public static final String freeMemorySize = "free_memory_size";
    public static final String totalDiskSize = "total_disk_size";
    public static final String diskPartitionInfo = "disk_partition_info";


    // Mysql数据库监控项目
    // 接收字节数
    public static final String BYTE_RECEIVE ="Bytes_received";
    // 发送字节数
    public static final String BYTE_SENT = "Bytes_sent";

    // 立即获得锁的次数
    public static final String TABLE_LOCKS_IMME = "Table_locks_immediate";
    // 等待获得锁的次数
    public static final  String  TABLE_LOCKS_WAITED = "Table_locks_waited";

    // 打开的连接数
    public static final String Connections = "Connections";
    // 中止连接数
    public static final String  ABORTED_CONNECTS = "Aborted_connects";
    // 中断客户数目
    public static final String  ABORTED_CLIENTS = "Aborted_connects";

    // 缓存内存线程数
    public static final String THREADS_CACHED = "Threads_cached";
    // 使用线程数
    public static final String THREADS_RUNNING = "Threads_running";

    // 请求命中数
    // http://dba.stackexchange.com/questions/7344/optimizing-mysql-query-cache-size
    public static final String QCACHE_HITS = "Qcache_hits";
    public static final String QCACHE_NOT_CACHED = "Qcache_not_cached";
    public static final String QCACHE_INSERTS = "Qcache_inserts";
    public static final String QCACHE_TOTAL_BLOCKS= "Qcache_total_blocks";
    public static final String QCACHE_RATE = "Qcache_rate";
    
    // 开机时间
    public static final String MYSQL_UPTIME = "Uptime";
    
    
    
    //mysql基本信息
    public static final String MYSQL_VERSION = "version";
    public static final String MYSQL_BASE_DIR = "basedir";
    public static final String MYSQL_DATA_DIR = "datadir";
    public static final String MYSQL_HOST_OS = "version_compile_os";
    public static final String MYSQL_HOST_NAME = "hostname";

}
