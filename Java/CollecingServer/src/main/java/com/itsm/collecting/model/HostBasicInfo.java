package com.itsm.collecting.model;

public class HostBasicInfo {
    private Integer hostId;

    private String hostIp;

    private String hostOs;

    private String deviceName;

    private String hostName;

    private Integer hostType;

    private String hostApplySystem;

    private Integer hostStatus;

    public Integer getHostId() {
        return hostId;
    }

    public void setHostId(Integer hostId) {
        this.hostId = hostId;
    }

    public String getHostIp() {
        return hostIp;
    }

    public void setHostIp(String hostIp) {
        this.hostIp = hostIp == null ? null : hostIp.trim();
    }

    public String getHostOs() {
        return hostOs;
    }

    public void setHostOs(String hostOs) {
        this.hostOs = hostOs == null ? null : hostOs.trim();
    }

    public String getDeviceName() {
        return deviceName;
    }

    public void setDeviceName(String deviceName) {
        this.deviceName = deviceName == null ? null : deviceName.trim();
    }

    public String getHostName() {
        return hostName;
    }

    public void setHostName(String hostName) {
        this.hostName = hostName == null ? null : hostName.trim();
    }

    public Integer getHostType() {
        return hostType;
    }

    public void setHostType(Integer hostType) {
        this.hostType = hostType;
    }

    public String getHostApplySystem() {
        return hostApplySystem;
    }

    public void setHostApplySystem(String hostApplySystem) {
        this.hostApplySystem = hostApplySystem == null ? null : hostApplySystem.trim();
    }

    public Integer getHostStatus() {
        return hostStatus;
    }

    public void setHostStatus(Integer hostStatus) {
        this.hostStatus = hostStatus;
    }
}