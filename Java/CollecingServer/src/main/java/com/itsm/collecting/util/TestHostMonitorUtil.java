package com.itsm.collecting.util;

import com.itsm.collecting.model.Disk;
import org.apache.ibatis.annotations.Param;
import org.snmp4j.smi.OID;
import org.snmp4j.smi.VariableBinding;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.Callable;
import org.apache.log4j.*;

/**
 * Created by CM on 2016/8/23.
 */
public class TestHostMonitorUtil implements Callable<Integer> {
    private String ip_;
    private String os_;
    private List<String> oids_ = new ArrayList<String>();
    private static  Logger logger = Logger.getLogger(TestHostMonitorUtil.class);

    public TestHostMonitorUtil(String ip, String os) {
        ip_ = ip;
        os_ = os;
        oids_.add(OIDConstants.LINUX_CPU_IDLE_PERCENT);
        oids_.add(OIDConstants.LINUX_TOTAL_MEMORY_SIZE);
        oids_.add(OIDConstants.LINUX_FREE_MEMORY_SIZE);
        oids_.add(OIDConstants.LINUX_TOTAL_DISK_SIZE);
    }


    public Integer call() throws Exception {
        if(!StringUtil.isStrNull(ip_) && !StringUtil.isStrNull(os_)) {
            if(os_.equals("linux")) {

                List<VariableBinding> vb = Snmp4JGet.getInstance().snmpGetList(ip_, "public", oids_);

                if (isDataValid(vb)) {
                    return 1;

                } else {
                    logger.error("response timeout ");
                    return 0;
                }
            }

            else if(os_.equals("windows")) {
                Map cpu_usage = Snmp4JGetWalk.getInstance().queryWalkTabData(ip_, "public", OIDConstants.WIN_CPU_USAGE);
                Map disk_table = Snmp4JGetWalk.getInstance().queryWalkTabData(ip_, "public", OIDConstants.WIN_DISK_PARTION_TABLE);
                Map disk_total_unit_num = Snmp4JGetWalk.getInstance().queryWalkTabData(ip_, "public", OIDConstants.WIN_DISK_TOTAL_UNIT_NUM);
                Map disk_used = Snmp4JGetWalk.getInstance().queryWalkTabData(ip_, "public", OIDConstants.WIN_DISK_USED);
                Map disk_unit_size = Snmp4JGetWalk.getInstance().queryWalkTabData(ip_, "public", OIDConstants.WIN_DISK_UNIT_SIZE);
                if(cpu_usage.size() != 0 && disk_table.size() != 0 && disk_total_unit_num.size() !=0 && disk_used.size() != 0 && disk_unit_size.size() != 0 ) {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        } else {
            return 0;
        }

    }

    private boolean isDataValid(List<VariableBinding> vb) {
        if(vb != null && vb.size() == 4) {
            return true;
        } else {
            return false;
        }
    }

}
