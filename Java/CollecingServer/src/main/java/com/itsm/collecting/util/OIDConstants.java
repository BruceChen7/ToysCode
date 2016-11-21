package com.itsm.collecting.util;

public class OIDConstants {
	// ip地址表OID
	public static String IPTABLEOID = "1.3.6.1.2.1.4.20.1.1";
	// 子网掩码OID
	public static String NETMASKTABLEOID = "1.3.6.1.2.1.4.20.1.3";
	// 系统运行时间OID
	public static String SYSUPTIME = "1.3.6.1.2.1.1.3";
	// 系统表OID
	public static String HRSYSTEM = "1.3.6.1.2.1.25.1";
	// 系统运行时间OID
	public static String HRSYSTEMUPTIME = "1.3.6.1.2.1.25.1.1";
	// 系统
	public static String HRSYSTEMUPDATE = "1.3.6.1.2.1.25.1.2";
	// 系统初始加载驱动OID
	public static String HRSYSTEMINITIALLOADDEVICE = "1.3.6.1.2.1.25.1.3";
	// 系统初始加载参数OID
	public static String HRSYSTEMINITIALLOADPARAMETERS = "1.3.6.1.2.1.25.1.4";
	// 系统用户数量OID
	public static String HRSYSTEMNUMUSERS = "1.3.6.1.2.1.25.1.5";
	// 系统处理器数量OID
	public static String HRSYSTEMPROCESSES = "1.3.6.1.2.1.25.1.6";
	// 系统最大处理器数量OID
	public static String HRSYSTEMMAXPROCESSES = "1.3.6.1.2.1.25.1.7";

	/************ start --存储器表-- ***********/
	// 存储器IOD
	public static String HRSTORAGE = "1.3.6.1.2.1.25.2";
	// 存储器类型集合OID
	public static String HRSTORAGETYPES = "1.3.6.1.2.1.25.2.1";
	// 内存大小OID
	public static String HRMEMORYSIZE = "1.3.6.1.2.1.25.2.2";
	// 存储器表OID
	public static String HRSTORAGETABLE = "1.3.6.1.2.1.25.2.3";
	// 存储器表集合OID
	public static String HRSTORAGEENTRY = "1.3.6.1.2.1.25.2.3.1";
	// 存储器序列号集合OID
	public static String HRSTORAGEINDEX = "1.3.6.1.2.1.25.2.3.1.1";
	// 存储器类型集合OID
	public static String HRSTORAGETYPE = "1.3.6.1.2.1.25.2.3.1.2";
	// 存储器描述集合OID
	public static String HRSTORAGEDESCR = "1.3.6.1.2.1.25.2.3.1.3";
	// 存储器允许的单元大小OID
	public static String HRSTORAGEALLOCATIONUNITS = "1.3.6.1.2.1.25.2.3.1.4";
	// 存储器大小集合OID
	public static String HRSTORAGESIZE = "1.3.6.1.2.1.25.2.3.1.5";
	// 存储器被使用的集合OID
	public static String HRSTORAGEUSED = "1.3.6.1.2.1.25.2.3.1.6";
	// 存储器被使用失误集合OID
	public static String HRSTORAGEALLOCATIONFAILURES = "1.3.6.1.2.1.25.2.3.1.7";
	/************ end --存储器表-- ***********/

	/************ start --驱动表-- ***********/
	// 系统驱动OID
	public static String HRDEVICE = "1.3.6.1.2.1.25.3";
	// 系统驱动类型表OID
	public static String HRDEVICETYPES = "1.3.6.1.2.1.25.3.1";
	// 系统驱动表OID
	public static String HRDEVICETABLE = "1.3.6.1.2.1.25.3.2";
	// 系统驱动实例表OID
	public static String HRDEVICEENTRY = "1.3.6.1.2.1.25.3.2.1";
	// 系统驱动序列号集合OID
	public static String HRDEVICEINDEX = "1.3.6.1.2.1.25.3.2.1.1";
	// 系统驱动类型集合OID
	public static String HRDEVICETYPE = "1.3.6.1.2.1.25.3.2.1.2";
	// 系统驱动描述集合OID
	public static String HRDEVICEDESCR = "1.3.6.1.2.1.25.3.2.1.3";
	// 系统驱动标识符集合OID
	public static String HRDEVICEID = "1.3.6.1.2.1.25.3.2.1.4";
	// 系统驱动状态集合OID
	public static String HRDEVICESTATUS = "1.3.6.1.2.1.25.3.2.1.5";
	// 系统驱动错误集合OID
	public static String HRDEVICEERRORS = "1.3.6.1.2.1.25.3.2.1.6";
	/************ end --驱动表-- ***********/

	/************ start --处理器表-- ***********/
	// 系统处理器表OID
	public static String HRPROCESSORTABLE = "1.3.6.1.2.1.25.3.3";
	// 系统处理器实例表OID
	public static String HRPROCESSORENTRY = "1.3.6.1.2.1.25.3.3.1";
	// 系统处理器标识符集合OID
	public static String HRPROCESSORFRWID = "1.3.6.1.2.1.25.3.3.1.1";
	// 系统处理器使用率集合OID（会有几个值，和CPU个数相关）
	/**
	 * 系统处理器使用率集合OID（会有几个值，和CPU个数相关）
	 */
	public static String HRPROCESSORLOAD = "1.3.6.1.2.1.25.3.3.1.2";
	/************ end --处理器表-- ***********/

	/************ start --网络表-- ***********/
	// 系统网络表OID
	public static String HRNETWORKTABLE = "1.3.6.1.2.1.25.3.4";
	// 系统网络实例表OID
	public static String HRNETWORKENTRY = "1.3.6.1.2.1.25.3.4.1";
	// 系统网络实例表OID
	public static String HRNETWORKIFINDEX = "1.3.6.1.2.1.25.3.4.1.1";
	/************ end --网络表-- ***********/

	/************ start --打印机表-- ***********/
	// 系统打印机表OID
	public static String HRPRINTERTABLE = "1.3.6.1.2.1.25.3.5";
	// 系统打印机实例表OID
	public static String HRPRINTERENTRY = "1.3.6.1.2.1.25.3.5.1";
	// 系统打印机状态OID
	public static String HRPRINTERSTATUS = "1.3.6.1.2.1.25.3.5.1.1";
	// 系统打印机错误状态OID
	public static String HRPRINTERDETECTEDERRORSTATE = "1.3.6.1.2.1.25.3.5.1.2";
	/************ end --打印机表-- ***********/

	/************ start --磁盘表-- ***********/
	// 磁盘存储器表OID
        public static String HRDISKSTORAGETABLE = "1.3.6.1.2.1.25.3.6";
	// 磁盘存储器实例表OID
	public static String HRDISKSTORAGEENTRY = "1.3.6.1.2.1.25.3.6.1";
	// 磁盘存储器表OID
	public static String HRDISKSTORAGEACCESS = "1.3.6.1.2.1.25.3.6.1.1";
	// 磁盘存储存OID
	public static String HRDISKSTORAGEMEDIA = "1.3.6.1.2.1.25.3.6.1.2";
	// 磁盘存储存OID
	public static String HRDISKSTORAGEREMOVEBLE = "1.3.6.1.2.1.25.3.6.1.3";
	// 磁盘存储存OID
	public static String HRDISKSTORAGECAPACITY = "1.3.6.1.2.1.25.3.6.1.4";
	/************ end --磁盘表-- ***********/

	/************ start --运行进程表-- ***********/
	// 正在运行的进程OID
	public static String HRSWRUN = "1.3.6.1.2.1.25.4";
	// 正在运行的进程序列号OID
	public static String HRSWOSINDEX = "1.3.6.1.2.1.25.4.1";
	// 正在运行的进程表OID
	public static String HRSWRUNTABLE = "1.3.6.1.2.1.25.4.2";
	// 正在运行的进程实例表OID
	public static String HRSWRUNENTRY = "1.3.6.1.2.1.25.4.2.1";
	// 正在运行的进程实例序列号OID
	public static String HRSWRUNINDEX = "1.3.6.1.2.1.25.4.2.1.1";
	// 正在运行的进程实例名称OID
	public static String HRSWRUNNAME = "1.3.6.1.2.1.25.4.2.1.2";
	// 正在运行的进程实例标识符OID
	public static String HRSWRUNID = "1.3.6.1.2.1.25.4.2.1.3";
	// 正在运行的进程实例路径OID
	public static String HRSWRUNPATH = "1.3.6.1.2.1.25.4.2.1.4";
	// 正在运行的进程实例参数OID
	public static String HRSWRUNPARAMETERS = "1.3.6.1.2.1.25.4.2.1.5";
	// 正在运行的进程实例类型OID
	public static String HRSWRUNTYPE = "1.3.6.1.2.1.25.4.2.1.6";
	// 正在运行的进程实例状态OID
	public static String HRSWRUNSTATUS = "1.3.6.1.2.1.25.4.2.1.7";
	/************ end --运行进程表-- ***********/

	/************ start --运行进程性能表-- ***********/
	// 正在运行的进程性能表OID
	/**
	 * 正在运行的进程性能表OID
	 */
	public static String HRSWRUNPERF = "1.3.6.1.2.1.25.5";
	// 正在运行的进程性能表OID
	public static String HRSWRUNPERFTABLE = "1.3.6.1.2.1.25.5.1";
	// 正在运行的进程性能实例表OID
	/**
	 * 正在运行的进程性能实例表OID
	 */
	public static String HRSWRUNPERFENTRY = "1.3.6.1.2.1.25.5.1.1";
	// 正在运行的进程性能实例表CPU性能OID
	public static String HRSWRUNPERFCPU = "1.3.6.1.2.1.25.5.1.1.1";
	// 正在运行的进程性能实例表内存性能OID
	public static String HRSWRUNPERFMEM = "1.3.6.1.2.1.25.5.1.1.2";
	/************ end --运行进程性能表-- ***********/

	/************ start --运行进程安装表-- ***********/
	// 安装程序对应OID
	public static String HRSWINSTALLED = "1.3.6.1.2.1.25.6";
	// 安装程序最后被改变时间（从开机时间开始算）OID
	public static String HRSWINSTALLEDLASTCHANGE = "1.3.6.1.2.1.25.6.1";
	// 安装程序最后更新时间（从开机时间开始算）OID
	public static String HRSWINSTALLEDLASTUPDATETIME = "1.3.6.1.2.1.25.6.2";
	// 安装程序表OID
	public static String HRSWINSTALLEDTABLE = "1.3.6.1.2.1.25.6.3";
	// 安装程序实例表OID
	public static String HRSWINSTALLEDENTRY = "1.3.6.1.2.1.25.6.3.1";
	// 安装程序序列号OID
	public static String HRSWINSTALLEDINDEX = "1.3.6.1.2.1.25.6.3.1.1";
	// 安装程序名称OID
	public static String HRSWINSTALLEDNAME = "1.3.6.1.2.1.25.6.3.1.2";
	// 安装程序标识符OID
	public static String HRSWINSTALLEDID = "1.3.6.1.2.1.25.6.3.1.3";
	// 安装程序类型OID
	public static String HRSWINSTALLEDTYPE = "1.3.6.1.2.1.25.6.3.1.4";
	// 安装程序时间OID
	public static String HRSWINSTALLEDDATE = "1.3.6.1.2.1.25.6.3.1.5";
	/************ end --运行进程安装表-- ***********/
	
	/************ start --网络接口表-- ***********/
	// 网络接口表 OID
	public static String IFTABLE = "1.3.6.1.2.1.2.2.1";
	// 网络接口OID
	public static String IFNUMBER = "1.3.6.1.2.1.2.1.0";
	// 网络接口信息描述OID
	public static String IFDESCR = "1.3.6.1.2.1.2.2.1.2";
	// 网络接口类型OID
    public static String IFTYPE = "1.3.6.1.2.1.2.2.1.3";
    // 接口发送和接收的最大IP数据报[BYTE]OID
    public static String IFMTU = "1.3.6.1.2.1.2.2.1.4";
    // 接口当前带宽[bps]OID
    public static String IFSPEED = "1.3.6.1.2.1.2.2.1.5";
    // 接口的物理地址OID
    public static String IFPHYSADDRESS = "1.3.6.1.2.1.2.2.1.6";
    // 接口当前操作状态[up|down]OID
    public static String IFOPERSTATUS = "1.3.6.1.2.1.2.2.1.8";
    // 接口收到的字节数OID
    public static String IFINOCTET = "1.3.6.1.2.1.2.2.1.10";
    // 接口收发送的字节数OID
    public static String IFOUTOCTET = "1.3.6.1.2.1.2.2.1.16";
    // 接口收到的数据包个数OID
    public static String IFINUCASTPKTS = "1.3.6.1.2.1.2.2.1.11";
    // 接口发送的数据包个数OID
    public static String IFOUTUCASTPKTS = "1.3.6.1.2.1.2.2.1.17";
	/************ end --网络接口表-- ***********/

    /*
     * 主机OID的参数
     */
    // http://www.net-snmp.org/docs/mibs/host.html
    public static String LINUX_CPU_IDLE_PERCENT = "1.3.6.1.4.1.2021.11.11.0";
    public static String LINUX_TOTAL_MEMORY_SIZE = "1.3.6.1.4.1.2021.4.5.0";
//    public static String USED_MEMORY_SIZE = "1.3.6.1.4.1.2021.4.6.0";
//    public static String LINUX_FREE_MEMORY_SIZE = "1.3.6.1.4.1.2021.4.11.0";
    // 这里只计算了实际物理内存的空闲空间，不包括磁盘交换区的
    public static String LINUX_FREE_MEMORY_SIZE = "1.3.6.1.4.1.2021.4.6.0";
    public static String LINUX_TOTAL_DISK_SIZE = "1.3.6.1.4.1.2021.9.1.6.1";
    public static String LINUX_DISK_PARTITION_INFO = "1.3.6.1.2.1.25.2.3";

    public static String WIN_MEMORY_SIZE = "1.3.6.1.2.1.25.2.2.0";
    public static String WIN_CPU_USAGE = ".1.3.6.1.2.1.25.3.3.1.2";
    public static String WIN_DISK_PARTION_TABLE = ".1.3.6.1.2.1.25.2.3.1.3";
    public static String WIN_DISK_UNIT_SIZE = ".1.3.6.1.2.1.25.2.3.1.4";
    public static String WIN_DISK_USED = ".1.3.6.1.2.1.25.2.3.1.6";
    public static String WIN_DISK_TOTAL_UNIT_NUM = ".1.3.6.1.2.1.25.2.3.1.5";


}
