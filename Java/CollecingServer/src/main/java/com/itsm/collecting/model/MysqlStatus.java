package com.itsm.collecting.model;

/**
 * Created by CM on 2016/8/11.
 */
public class MysqlStatus  extends MySqlMonitorInfo {
    public String getOs() {
        return os;
    }

    public void setOs(String os) {
        this.os = os;
    }

    private String  os;

    public String getIpAddress() {
        return ip_address;
    }

    public void setIpAddress(String ip_address) {
        this.ip_address = ip_address;
    }

    public void setApplicationName(String name) {
        application_name = name;
    }

    public String getApplicationName() {
        return application_name;
    }

    private String ip_address;
    private String application_name;


}
