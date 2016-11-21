package com.itsm.collecting.util;

import com.itsm.collecting.dao.HostDataInfoMapper;
import com.itsm.collecting.model.Disk;
import com.itsm.collecting.model.HostBasicInfo;
import com.itsm.collecting.model.HostDataInfo;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.log4j.Logger;
import org.snmp4j.smi.VariableBinding;
import redis.clients.jedis.Jedis;

import java.text.DecimalFormat;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.Future;


/**
 * Created by CM on 2016/7/20.
 */
public class HostCollectingTask implements Runnable {
    private static Logger logger = Logger.getLogger(HostCollectingTask.class);
    private HostBasicInfo host_info;
    private ConcurrentHashMap<String,Future> host_future_map;
    private List<String> oids = new ArrayList<String>();

    public HostCollectingTask(ConcurrentHashMap<String,Future> host_future_map,HostBasicInfo info) {
        this.host_info = info;
        this.host_future_map = host_future_map;
        if(host_info.getHostOs().equals("linux")) {
            oids.clear();
            oids.add(OIDConstants.LINUX_CPU_IDLE_PERCENT);
            oids.add(OIDConstants.LINUX_TOTAL_MEMORY_SIZE);
            oids.add(OIDConstants.LINUX_FREE_MEMORY_SIZE);
            oids.add(OIDConstants.LINUX_TOTAL_DISK_SIZE);
        } else if(host_info.getHostOs().equals("windows")) {
            oids.clear();
            oids.add(OIDConstants.WIN_CPU_USAGE);
            oids.add(OIDConstants.WIN_MEMORY_SIZE);
            oids.add(OIDConstants.WIN_DISK_PARTION_TABLE);
        } else {
            assert (0 == 1);
        }
    }


    public void run() {
    	String value = host_info.getHostIp()+":"+host_info.getHostOs() + ":" +host_info.getHostId();
    	JedisPoolUtils.initPool();
    	Jedis jedis = JedisPoolUtils.getResource();
    	List<String> coll_host_info = jedis.lrange(Constants.COLLECTING_HOST_INFO, 0, -1);
    	logger.info(value);
    	JedisPoolUtils.returnResource(jedis);
    	if(!coll_host_info.contains(value)){
    		Future future = host_future_map.remove(host_info.getHostIp());
    		future.cancel(true);
    		logger.info(host_info.getHostIp()+"Collecting has been cancled");
    		return;
    	}
        String ip = host_info.getHostIp();
        assert (!StringUtil.isStrNull(ip));
        int ts = TimeTrans.getCurrentTimestamp();

        String os = host_info.getHostOs();
        logger.info("ip is " + ip);
        logger.info("os is " + os);
        try {
            if(os.equals("linux")) {

                List<VariableBinding> vb = Snmp4JGet.getInstance().snmpGetList(ip, "public", oids);

                if (isDataValid(vb)) {
                    Map<String, VariableBinding> data = Snmp4JGetWalk.getInstance().snmpWalk(ip, "public", OIDConstants.LINUX_DISK_PARTITION_INFO);
                    Disk disk =  Disk.parseCollectingDiskData(data);
                    logger.info("begin to insert data to redis ");
                    insertLinuxDataToRedisAndDataBase(vb, ip, ts, disk);
                    return;

                } else {
                    logger.error("response timeout ");
                    return;

                }
            } // linux collectin end


            if(os.equals("windows")) {
                Map cpu_usage = Snmp4JGetWalk.getInstance().queryWalkTabData(ip, "public", OIDConstants.WIN_CPU_USAGE);
                Map disk_table = Snmp4JGetWalk.getInstance().queryWalkTabData(ip, "public", OIDConstants.WIN_DISK_PARTION_TABLE);
                logger.info("disk table is " + disk_table);
                Map disk_total_unit_num = Snmp4JGetWalk.getInstance().queryWalkTabData(ip, "public", OIDConstants.WIN_DISK_TOTAL_UNIT_NUM);
                logger.info("disk unit num " + disk_total_unit_num);
                Map disk_used = Snmp4JGetWalk.getInstance().queryWalkTabData(ip, "public", OIDConstants.WIN_DISK_USED);
                logger.info("disk used " + disk_used);
                Map disk_unit_size = Snmp4JGetWalk.getInstance().queryWalkTabData(ip, "public", OIDConstants.WIN_DISK_UNIT_SIZE);
                logger.info("unit size " + disk_unit_size);
                insertWindowsDataToRedis(disk_table, disk_total_unit_num, disk_used, disk_unit_size, cpu_usage, ts);
                return;

            }
        } catch (Exception e) {
            logger.error("系统出错", e);
        }
    }

    private void insertWindowsDataToRedis(Map disk_table, Map disk_total_unit_num, Map disk_used, Map disk_unit_size, Map cpu_usage, int ts) {
        assert (disk_table.size() == disk_total_unit_num.size());
        assert (disk_used.size() == disk_table.size());
        assert (disk_unit_size.size() == disk_table.size());

        JedisPoolUtils.initPool();
        Jedis jedis = JedisPoolUtils.getResource();
        logger.info("get jedis");

        SqlSession s = null;

        SqlSessionFactory factory = SqlSessionUtil.getSqlSession();
        s = factory.openSession(true);
        if(factory == null) {
            return;
        }

        try {

            String disk_str = "";
            int n = 0;

            long total_disk_size = 0;
            long total_memory_size = 0;
            long used_memory_size = 0;

            for(Iterator<String> it = disk_table.keySet().iterator(); it.hasNext();) {
                n++;
                String key = it.next();

                List<String> table_str = (List<String>)disk_table.get(key);
                List<String> unit_size_str = (List<String>)disk_unit_size.get(key);
                List<String> use_size_str = (List<String>)disk_used.get(key);
                List<String> total_size_str = (List<String>)disk_total_unit_num.get(key);


                if(isValidDiskTableDesc(table_str)) {

                    String disk_desc = constructValidWindowsPartitionName(table_str.get(0));
                    disk_str += disk_desc;

                    assert(unit_size_str.size() == 1);
                    assert(use_size_str.size() == 1);
                    assert(total_size_str.size() == 1);
                    Integer unit_size = Integer.parseInt(unit_size_str.get(0));
                    long used_size = Integer.parseInt(use_size_str.get(0));
                    long total_size = Integer.parseInt(total_size_str.get(0));

                    double used_size_gb = Disk.convertByteToGB(unit_size * used_size);

                    double total_size_gb  = Disk.convertByteToGB(total_size * unit_size);
                    total_disk_size += total_size * unit_size;
                    double usage_rate =  Double.parseDouble(new DecimalFormat("##########0.00").format((double)used_size_gb /(double)total_size_gb));
                    
                    logger.info("windows partation usage is "+ usage_rate);
                    
                    disk_str +="-"+total_size_gb + "-"+ used_size_gb + "-"+usage_rate;
                   
                    if(n != disk_table.size()) {

                        disk_str += ":";
                    }

                }
                // 内存采集
                if(table_str.get(0).equals("Physical Memory")) {
                    long used_memory_num = Integer.parseInt(use_size_str.get(0));
                    long total_memory_num = Integer.parseInt(total_size_str.get(0));
                    Integer unit_memory_size = Integer.parseInt(unit_size_str.get(0));

                    total_memory_size = total_memory_num * unit_memory_size;
                    used_memory_size = used_memory_num * unit_memory_size;

                }

            }

            if(disk_str.charAt(disk_str.length() - 1) == ':') {
                disk_str = disk_str.substring(0, disk_str.length() - 1);
            }


            double cpu_average = 0.0;
            double cpu_sum = 0.0;
            for(Iterator<String> it = cpu_usage.keySet().iterator(); it.hasNext();) {
                String key = it.next();
                List<String> c = (List<String>)cpu_usage.get(key);
                assert(c.size() == 1);
                cpu_sum += Double.parseDouble(c.get(0));
            }
            cpu_average = cpu_sum / (cpu_usage.size());
            
            logger.info("host disk usage detail is"+disk_str);
            
            HostDataInfo data = new HostDataInfo();
            data.setDiskPartitionUsage(disk_str);
            data.setDateTime(ts);
            

            // 有溢出的危险
            data.setDiskTotalSize(total_disk_size);
            data.setMemoryCapacity(total_memory_size);
            data.setMemoryUsage(used_memory_size);
            data.setCpuUsageRate(cpu_average);
            data.setHostId(host_info.getHostId());
            
            
            logger.info("insert db host disk usage detail is"+ data.getDiskPartitionUsage());

            HostDataInfoMapper mapper = s.getMapper(HostDataInfoMapper.class);
            int res= mapper.insertSelective(data);

            String ip = host_info.getHostIp();

            if(res == 1) {

                if(jedis != null) {
                    jedis.lpush(ip, ip + ":" + ts);
                    // 如果长度超过了200万条，缩减为100万。
                    if (jedis.llen(ip) >= Constants.MaxListValueNum) {
                        jedis.ltrim(ip, 0, Constants.MaxListValueNum / 2 - 1);
                    }

                    Map<String, String> hash_data = constructHashTable((int)cpu_average, total_memory_size, total_memory_size - used_memory_size, total_disk_size, disk_str, ts);
                    jedis.hmset(Constants.HASH_TABLE_NAME, hash_data);
                    jedis.expire(Constants.HASH_TABLE_NAME, Constants.ONE_WEEK);
                } else {
                    logger.error("redis get error");
                }

            }
        } catch (Exception e) {
            logger.error("系统出错", e);
        } finally {


            if(s != null) {
                s.close();

            }
            JedisPoolUtils.returnResource(jedis);
        }


    }

    private String constructValidWindowsPartitionName(String s) {
        String[] desc = s.split(("\\\\"));
        assert (desc.length != 1);
        return desc[0].split(":")[0];
    }

    private boolean isValidDiskTableDesc(List<String> table_str) {
        if(table_str != null && table_str.size() == 1) {
            if(table_str.get(0).split("\\\\").length != 1) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    private boolean isDataValid(List<VariableBinding> vb) {
        if(vb != null && vb.size() == 4) {
            return true;
        } else {
            return false;
        }
    }

    private String constructHashKey(String ip, String index_name, int ts) {
        return ip + ":" + index_name + ":" + ts;
    }


    private Map<String, String> constructHashTable(int cpu_usage, long memory_size, long free_memory_size, long total_disk_size, String disk_partition, int ts) {
        String ip = host_info.getHostIp();
        Map<String, String> host_data = new HashMap<String, String>();

        String memory_size_key = constructHashKey(ip, CollectingIndexName.memorySize, ts);
        String used_memory_key = constructHashKey(ip, CollectingIndexName.usedMemorySize, ts);
        String free_memory_key = constructHashKey(ip, CollectingIndexName.freeMemorySize, ts);
        String total_disk_key= constructHashKey(ip, CollectingIndexName.totalDiskSize, ts);
        String disk_partition_key = constructHashKey(ip, CollectingIndexName.diskPartitionInfo, ts);
        String cpu_usage_key = constructHashKey(ip, CollectingIndexName.cpuUsage, ts);

        
        logger.info("内存总容量为："+memory_size);
        logger.info("内存空闲容量为: "+free_memory_size);
        logger.info("内存已使用:"+(memory_size-free_memory_size));
        
        host_data.put(cpu_usage_key, "" + cpu_usage);
        host_data.put(memory_size_key, "" + memory_size);
        host_data.put(used_memory_key, "" + (memory_size - free_memory_size));
        host_data.put(free_memory_key, "" + free_memory_size);
        host_data.put(total_disk_key, "" + total_disk_size);
        host_data.put(disk_partition_key, disk_partition);
        
        logger.info("内存usage in database is "+host_data.get(used_memory_key));

        return  host_data;

    }

    private void insertLinuxDataToRedisAndDataBase(List<VariableBinding> vb, String ip, int ts, Disk disk) {
        Map<String, String> host_data = new HashMap<String, String>();

        SqlSession s = null;
        logger.info("begin data process-------");
        SqlSessionFactory factory = SqlSessionUtil.getSqlSession();
        logger.info("get sqlfactory successfully!");
        JedisPoolUtils.initPool();
        logger.info("begin to get resource  " );
        Jedis jedis = JedisPoolUtils.getResource();
        logger.info("insert to redis  to " );


        try {
            Integer cpu_usage = 100 - vb.get(0).getVariable().toInt();
            if(cpu_usage <=  0) {
                cpu_usage = 0;
            }

            long memory_size = vb.get(1).getVariable().toLong();
            long free_memory_size = vb.get(2).getVariable().toLong();
            long total_disk_size = vb.get(3).getVariable().toInt();

            String memory_size_key = constructHashKey(ip, CollectingIndexName.memorySize, ts);
            String used_memory_key = constructHashKey(ip, CollectingIndexName.usedMemorySize, ts);
            String total_disk_key= constructHashKey(ip, CollectingIndexName.totalDiskSize, ts);
            
            logger.info("内存容量为： "+memory_size);
            logger.info("空闲内存容量为："+free_memory_size);
            
            host_data = constructHashTable(cpu_usage, memory_size, free_memory_size, total_disk_size, disk.toString(), ts);

            s = factory.openSession(true);

            if( s == null) {
                return;
            }

            HostDataInfoMapper mapper = s.getMapper(HostDataInfoMapper.class);

            HostDataInfo info = new HostDataInfo();
            info.setHostId(host_info.getHostId());
            info.setCpuUsageRate((Double.parseDouble("" + cpu_usage)));
            info.setMemoryCapacity((Long.parseLong(host_data.get(memory_size_key))));
            info.setMemoryUsage(Long.parseLong(host_data.get(used_memory_key)));
            info.setDiskTotalSize(Long.parseLong(host_data.get(total_disk_key)));
            info.setDiskPartitionUsage(disk.toString());
            info.setDateTime(ts);
            
            logger.info("已使用内存容量为:"+info.getMemoryUsage());

            int res = mapper.insertSelective(info);
            if(res == 1) {
                logger.info("push ip to redis");
                if(jedis != null) {
                    jedis.lpush(ip, ip + ":" + ts);
                    // 如果长度超过了200万条，缩减为100万。
                    if (jedis.llen(ip) >= Constants.MaxListValueNum) {
                        jedis.ltrim(ip, 0, Constants.MaxListValueNum / 2 - 1);
                    }
                    jedis.hmset(Constants.HASH_TABLE_NAME, host_data);
                    jedis.expire(Constants.HASH_TABLE_NAME, Constants.ONE_WEEK);
                } else {
                    logger.error("get jedis resource error");
                }

            }

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if(s != null) {
                s.close();
            }
            JedisPoolUtils.returnResource(jedis);
        }
    }
}
