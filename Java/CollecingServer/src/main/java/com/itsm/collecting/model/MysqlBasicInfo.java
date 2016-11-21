package com.itsm.collecting.model;

public class MysqlBasicInfo {
    private Integer mysqlId;

    private String mysqlVersion;

    private String mysqlBaseDir;

    private String mysqlDataDir;

    private String mysqlHostName;

    private String mysqlHostOs;

    private String mysqlDbSizeList;

    private String mysqlDbNameList;

    public Integer getMysqlId() {
        return mysqlId;
    }

    public void setMysqlId(Integer mysqlId) {
        this.mysqlId = mysqlId;
    }

    public String getMysqlVersion() {
        return mysqlVersion;
    }

    public void setMysqlVersion(String mysqlVersion) {
        this.mysqlVersion = mysqlVersion == null ? null : mysqlVersion.trim();
    }

    public String getMysqlBaseDir() {
        return mysqlBaseDir;
    }

    public void setMysqlBaseDir(String mysqlBaseDir) {
        this.mysqlBaseDir = mysqlBaseDir == null ? null : mysqlBaseDir.trim();
    }

    public String getMysqlDataDir() {
        return mysqlDataDir;
    }

    public void setMysqlDataDir(String mysqlDataDir) {
        this.mysqlDataDir = mysqlDataDir == null ? null : mysqlDataDir.trim();
    }

    public String getMysqlHostName() {
        return mysqlHostName;
    }

    public void setMysqlHostName(String mysqlHostName) {
        this.mysqlHostName = mysqlHostName == null ? null : mysqlHostName.trim();
    }

    public String getMysqlHostOs() {
        return mysqlHostOs;
    }

    public void setMysqlHostOs(String mysqlHostOs) {
        this.mysqlHostOs = mysqlHostOs == null ? null : mysqlHostOs.trim();
    }

    public String getMysqlDbSizeList() {
        return mysqlDbSizeList;
    }

    public void setMysqlDbSizeList(String mysqlDbSizeList) {
        this.mysqlDbSizeList = mysqlDbSizeList == null ? null : mysqlDbSizeList.trim();
    }

    public String getMysqlDbNameList() {
        return mysqlDbNameList;
    }

    public void setMysqlDbNameList(String mysqlDbNameList) {
        this.mysqlDbNameList = mysqlDbNameList == null ? null : mysqlDbNameList.trim();
    }
}