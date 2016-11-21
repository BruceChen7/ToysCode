package com.itsm.collecting.model;

public class MssqlBasicInfo {
    private Integer mssqlId;

    private String mssqlVersion;

    private String mssqlMonitorServiceType;

    private String mssqlOdbcVersion;

    private String mssqlHostName;

    private String mssqlHostOs;

    public Integer getMssqlId() {
        return mssqlId;
    }

    public void setMssqlId(Integer mssqlId) {
        this.mssqlId = mssqlId;
    }

    public String getMssqlVersion() {
        return mssqlVersion;
    }

    public void setMssqlVersion(String mssqlVersion) {
        this.mssqlVersion = mssqlVersion == null ? null : mssqlVersion.trim();
    }

    public String getMssqlMonitorServiceType() {
        return mssqlMonitorServiceType;
    }

    public void setMssqlMonitorServiceType(String mssqlMonitorServiceType) {
        this.mssqlMonitorServiceType = mssqlMonitorServiceType == null ? null : mssqlMonitorServiceType.trim();
    }

    public String getMssqlOdbcVersion() {
        return mssqlOdbcVersion;
    }

    public void setMssqlOdbcVersion(String mssqlOdbcVersion) {
        this.mssqlOdbcVersion = mssqlOdbcVersion == null ? null : mssqlOdbcVersion.trim();
    }

    public String getMssqlHostName() {
        return mssqlHostName;
    }

    public void setMssqlHostName(String mssqlHostName) {
        this.mssqlHostName = mssqlHostName == null ? null : mssqlHostName.trim();
    }

    public String getMssqlHostOs() {
        return mssqlHostOs;
    }

    public void setMssqlHostOs(String mssqlHostOs) {
        this.mssqlHostOs = mssqlHostOs == null ? null : mssqlHostOs.trim();
    }
}