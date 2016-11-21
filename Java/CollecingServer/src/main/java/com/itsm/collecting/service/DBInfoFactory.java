package com.itsm.collecting.service;

import com.itsm.collecting.model.DatabaseBasicInfo;
import com.itsm.collecting.model.MysqlDBInfo;
import com.itsm.collecting.model.OracleDBInfo;
import com.itsm.collecting.model.SqlServerDBInfo;
import com.itsm.collecting.util.Constants;

/**
 * Created by CM on 2016/8/25.
 */
public class DBInfoFactory {
    public static DatabaseBasicInfo getDBObject(String type) {
        if(type.equals(Constants.MYSQL_DB)) {
            return new MysqlDBInfo();
        }
        else if(type.equals(Constants.ORACLE_DB)) {
            return new OracleDBInfo();
        }

        else if(type.equals(Constants.SQL_SERVER)) {
            return new SqlServerDBInfo();
        } else {
            return null;
        }
    }
}
