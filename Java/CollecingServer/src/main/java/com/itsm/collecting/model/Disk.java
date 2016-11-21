package com.itsm.collecting.model;

import com.itsm.collecting.util.OIDConstants;
import org.apache.log4j.Logger;
import org.snmp4j.smi.VariableBinding;

import java.text.DecimalFormat;
import java.util.*;

public class Disk {

    private static Logger logger =  Logger.getLogger(Disk.class);
	private List<Storage> storages;
	private double diskUesedRate;
	private float diskSpace;
	private float diskTotalSpace;
	
	public List<Storage> getStorages() {
		return storages;
	}

	public void setStorages(List<Storage> storages) {
		this.storages = storages;
	}

	public double getDiskUesedRate() {
		return diskUesedRate;
	}

	public void setDiskUesedRate(double diskUesedRate) {
		this.diskUesedRate = diskUesedRate;
	}

	public float getDiskSpace() {
		return diskSpace;
	}

	public void setDiskSpace(float diskSpace) {
		this.diskSpace = diskSpace;
	}

	public float getDiskTotalSpace() {
		return diskTotalSpace;
	}

	public void setDiskTotalSpace(float diskTotalSpace) {
		this.diskTotalSpace = diskTotalSpace;
	}

	@Override
	public String toString() {
        assert (storages != null);
        String res = "";
        for(int i = 0 ; i < storages.size(); i++) {
            Storage s = storages.get(i);
            res += s.getHrStorageDescr() + "-" + s.getHrStorageSize() + "-" + s.getHrStorageUsed() + "-" + s.getHrStorageUsedRate();
            if( i != storages.size() - 1) {
                res += ":";
            }
        }
        logger.info("res is " + res);
        return res;
	}


    public  static Disk   parseCollectingDiskData(Map<String, VariableBinding> data) {
        String hr_storage_table = OIDConstants.LINUX_DISK_PARTITION_INFO;
        String pattern = hr_storage_table + ".1.3";
        List<String> disk_index = getDiskIndexNum(pattern, data);
        Map<String, Integer> unit_size = getDiskUnitSize(data, disk_index);
        Disk disk = getDiskPartitionSize(unit_size, data, disk_index);

        // logger.info("hr storage table " + hr_storage_table);
        return disk;
    }

    public static Disk getDiskPartitionSize(Map<String, Integer> unit_size,
                                                            Map<String, VariableBinding> data,
                                                            List<String> index) {

        Disk disk = new Disk();
        List<Storage> storage = new ArrayList<Storage>();
        String oid_disk_size = OIDConstants.LINUX_DISK_PARTITION_INFO + ".1.5.";
        String oid_partition_name = OIDConstants.LINUX_DISK_PARTITION_INFO + ".1.3.";
        String oid_disk_used =  OIDConstants.LINUX_DISK_PARTITION_INFO + ".1.6.";

        for(String i : index) {
            Storage s = new Storage();
            // logger.info("i is " + i);
            int partition_unit_size = unit_size.get(i);
            // logger.info("partition unit size " + partition_unit_size);
            int allocation_unit = data.get(oid_disk_size + i).getVariable().toInt();

            Double  all_partition_size = Disk.convertByteToGB((long)allocation_unit * (long)partition_unit_size);
            String partition_name = data.get(oid_partition_name + i).getVariable().toString();


            double partition_used = Disk.convertByteToGB((long)data.get(oid_disk_used + i).getVariable().toInt() * (long)partition_unit_size);
            s.setHrStorageAllocationUnits(allocation_unit);
            s.setHrStorageSize(all_partition_size);
            s.setHrStorageDescr(partition_name);
            s.setHrStorageUsed(partition_used );
            
            
            
            
            String usage = new DecimalFormat("##0.0000").format((double)partition_used / (double)all_partition_size);
            
            logger.info("disk  partation usage is" + usage);
            
            Double usage_rate = Double.parseDouble(usage);
            if(usage_rate<0.01){
            	s.setHrStorageUsedRate(0);
            }
            else{
            	 s.setHrStorageUsedRate(usage_rate);
            }
       
            storage.add(s);
        }

        disk.setStorages(storage);
        return disk;
    }


    public static  Map<String, Integer> getDiskUnitSize(Map<String, VariableBinding> data, List<String> disk_index) {
        String unit_size_oid = OIDConstants.LINUX_DISK_PARTITION_INFO + ".1.4.";
        Map<String, Integer> unit_size = new HashMap<String, Integer>();

        for(String i  : disk_index) {
            String oid =  unit_size_oid + i;
            logger.info("oid is " + oid);
            unit_size.put(i, data.get(oid).getVariable().toInt());
        }
        return unit_size;
    }

    public static List<String> getDiskIndexNum(String pattern, Map<String, VariableBinding> data) {
        List<String> index = new ArrayList<String>();
        for(String key : data.keySet()) {
            if(key.contains(pattern) ) {
                String value = data.get(key).getVariable().toString();
                logger.info("value is " + value);

                if(value.startsWith("/")) {
                    String[] num = key.split("\\.");

                    index.add(num[num.length - 1]);
                }
            }
        }


        Collections.sort(index);
        for(String i : index) {
            logger.info(" index is " + i);
        }
        return index;


    }

    public static double convertByteToGB(long disk_size) {
        return Double.parseDouble(new DecimalFormat("##########0.00").format((double) disk_size / (double) 1024 / (double) 1024 / (double) 1024)) ;
    }
	
}
