package com.itsm.collecting.model;

public class HostDataInfo {
    private Integer recordId;

    private Integer hostId;

    private Integer dateTime;

    private Double cpuUsageRate;

    private Long memoryCapacity;

    private Long memoryUsage;

    private Long diskTotalSize;

    private String diskPartitionUsage;

    public Integer getRecordId() {
        return recordId;
    }

    public void setRecordId(Integer recordId) {
        this.recordId = recordId;
    }

    public Integer getHostId() {
        return hostId;
    }

    public void setHostId(Integer hostId) {
        this.hostId = hostId;
    }

    public Integer getDateTime() {
        return dateTime;
    }

    public void setDateTime(Integer dateTime) {
        this.dateTime = dateTime;
    }

    public Double getCpuUsageRate() {
        return cpuUsageRate;
    }

    public void setCpuUsageRate(Double cpuUsageRate) {
        this.cpuUsageRate = cpuUsageRate;
    }

    public Long getMemoryCapacity() {
        return memoryCapacity;
    }

    public void setMemoryCapacity(Long memoryCapacity) {
        this.memoryCapacity = memoryCapacity;
    }

    public Long getMemoryUsage() {
        return memoryUsage;
    }

    public void setMemoryUsage(Long memoryUsage) {
        this.memoryUsage = memoryUsage;
    }

    public Long getDiskTotalSize() {
        return diskTotalSize;
    }

    public void setDiskTotalSize(Long diskTotalSize) {
        this.diskTotalSize = diskTotalSize;
    }

    public String getDiskPartitionUsage() {
        return diskPartitionUsage;
    }

    public void setDiskPartitionUsage(String diskPartitionUsage) {
        this.diskPartitionUsage = diskPartitionUsage == null ? null : diskPartitionUsage.trim();
    }
}