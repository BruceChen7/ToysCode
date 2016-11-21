package com.itsm.collecting.model;

public class MySqlMonitorInfo {
    private Long id;

    private Integer dbId;

    private Integer connectionTime;

    private Integer requestRate;

    private Integer receiveByteRate;

    private Integer sendByteRate;

    private Integer openConnectionNum;

    private Integer terminateConnectionNum;

    private Integer terminateClientNum;

    private Integer useThreadNum;

    private Integer cachedMemoryThreadNum;

    private Integer cachedMemorySize;

    private String dbName;

    private Integer dbSize;

    private Integer immediateLockNum;

    private Integer waitLockNum;

    private Integer keyHitNum;

    private Integer usedCachedKeySize;

    private Integer keyCacehdSize;

    private Integer requestCachedHitRate;

    private Integer requestCachedSize;

    private Integer requestCachedMaxSize;

    private Integer healthStatus;

    private Integer monitorTime;

    private Integer upTime;

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Integer getDbId() {
        return dbId;
    }

    public void setDbId(Integer dbId) {
        this.dbId = dbId;
    }

    public Integer getConnectionTime() {
        return connectionTime;
    }

    public void setConnectionTime(Integer connectionTime) {
        this.connectionTime = connectionTime;
    }

    public Integer getRequestRate() {
        return requestRate;
    }

    public void setRequestRate(Integer requestRate) {
        this.requestRate = requestRate;
    }

    public Integer getReceiveByteRate() {
        return receiveByteRate;
    }

    public void setReceiveByteRate(Integer receiveByteRate) {
        this.receiveByteRate = receiveByteRate;
    }

    public Integer getSendByteRate() {
        return sendByteRate;
    }

    public void setSendByteRate(Integer sendByteRate) {
        this.sendByteRate = sendByteRate;
    }

    public Integer getOpenConnectionNum() {
        return openConnectionNum;
    }

    public void setOpenConnectionNum(Integer openConnectionNum) {
        this.openConnectionNum = openConnectionNum;
    }

    public Integer getTerminateConnectionNum() {
        return terminateConnectionNum;
    }

    public void setTerminateConnectionNum(Integer terminateConnectionNum) {
        this.terminateConnectionNum = terminateConnectionNum;
    }

    public Integer getTerminateClientNum() {
        return terminateClientNum;
    }

    public void setTerminateClientNum(Integer terminateClientNum) {
        this.terminateClientNum = terminateClientNum;
    }

    public Integer getUseThreadNum() {
        return useThreadNum;
    }

    public void setUseThreadNum(Integer useThreadNum) {
        this.useThreadNum = useThreadNum;
    }

    public Integer getCachedMemoryThreadNum() {
        return cachedMemoryThreadNum;
    }

    public void setCachedMemoryThreadNum(Integer cachedMemoryThreadNum) {
        this.cachedMemoryThreadNum = cachedMemoryThreadNum;
    }

    public Integer getCachedMemorySize() {
        return cachedMemorySize;
    }

    public void setCachedMemorySize(Integer cachedMemorySize) {
        this.cachedMemorySize = cachedMemorySize;
    }

    public String getDbName() {
        return dbName;
    }

    public void setDbName(String dbName) {
        this.dbName = dbName == null ? null : dbName.trim();
    }

    public Integer getDbSize() {
        return dbSize;
    }

    public void setDbSize(Integer dbSize) {
        this.dbSize = dbSize;
    }

    public Integer getImmediateLockNum() {
        return immediateLockNum;
    }

    public void setImmediateLockNum(Integer immediateLockNum) {
        this.immediateLockNum = immediateLockNum;
    }

    public Integer getWaitLockNum() {
        return waitLockNum;
    }

    public void setWaitLockNum(Integer waitLockNum) {
        this.waitLockNum = waitLockNum;
    }

    public Integer getKeyHitNum() {
        return keyHitNum;
    }

    public void setKeyHitNum(Integer keyHitNum) {
        this.keyHitNum = keyHitNum;
    }

    public Integer getUsedCachedKeySize() {
        return usedCachedKeySize;
    }

    public void setUsedCachedKeySize(Integer usedCachedKeySize) {
        this.usedCachedKeySize = usedCachedKeySize;
    }

    public Integer getKeyCacehdSize() {
        return keyCacehdSize;
    }

    public void setKeyCacehdSize(Integer keyCacehdSize) {
        this.keyCacehdSize = keyCacehdSize;
    }

    public Integer getRequestCachedHitRate() {
        return requestCachedHitRate;
    }

    public void setRequestCachedHitRate(Integer requestCachedHitRate) {
        this.requestCachedHitRate = requestCachedHitRate;
    }

    public Integer getRequestCachedSize() {
        return requestCachedSize;
    }

    public void setRequestCachedSize(Integer requestCachedSize) {
        this.requestCachedSize = requestCachedSize;
    }

    public Integer getRequestCachedMaxSize() {
        return requestCachedMaxSize;
    }

    public void setRequestCachedMaxSize(Integer requestCachedMaxSize) {
        this.requestCachedMaxSize = requestCachedMaxSize;
    }

    public Integer getHealthStatus() {
        return healthStatus;
    }

    public void setHealthStatus(Integer healthStatus) {
        this.healthStatus = healthStatus;
    }

    public Integer getMonitorTime() {
        return monitorTime;
    }

    public void setMonitorTime(Integer monitorTime) {
        this.monitorTime = monitorTime;
    }

    public Integer getUpTime() {
        return upTime;
    }

    public void setUpTime(Integer upTime) {
        this.upTime = upTime;
    }
}