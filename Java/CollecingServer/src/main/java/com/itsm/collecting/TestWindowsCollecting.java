package com.itsm.collecting;

import com.itsm.collecting.dao.HostBasicInfoMapper;
import com.itsm.collecting.model.HostBasicInfo;
import com.itsm.collecting.util.HostCollectingTask;
import com.itsm.collecting.util.SqlSessionUtil;
import org.apache.ibatis.session.SqlSession;
import org.apache.log4j.Logger;

import java.util.List;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

/**
 * Created by CM on 2016/8/15.
 */
public class TestWindowsCollecting {
    private static Logger logger = Logger.getLogger(TestWindowsCollecting.class);

    private static ScheduledExecutorService es;


    public TestWindowsCollecting() {
        int core_num = Runtime.getRuntime().availableProcessors();
        logger.info("core num is " + core_num);
        es =  Executors.newScheduledThreadPool(core_num);
    }


    public static void main(String[] args) throws Exception {

        SqlSession s = SqlSessionUtil.getSqlSession().openSession(true);
        TestWindowsCollecting server = new TestWindowsCollecting();

        List<HostBasicInfo> host_info;
        try {
            HostBasicInfo h = new HostBasicInfo();
            h.setHostIp("127.0.0.1");
            h.setHostOs("windows");
//            es.scheduleAtFixedRate(new HostCollectingTask(h), 0, 1, TimeUnit.MINUTES);


        } catch(Exception e) {
            e.printStackTrace();
        }  finally {
            logger.info("close right");
            s.close();
        }




    }
}
