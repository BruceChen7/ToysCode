package com.itsm.collecting.model;

public class DatabaseBasicInfo {
    private Integer id;

    private String dbName;

    private String dbIp;

    private String dbPort;

    private String dbType;

    private String appSystem;

    private Integer dbStatus;

    private String dbUsername;

    private String dbPassword;
    
    private String dbOracleSid;

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getDbName() {
        return dbName;
    }

    public void setDbName(String dbName) {
        this.dbName = dbName == null ? null : dbName.trim();
    }

    public String getDbIp() {
        return dbIp;
    }

    public void setDbIp(String dbIp) {
        this.dbIp = dbIp == null ? null : dbIp.trim();
    }

    public String getDbPort() {
        return dbPort;
    }

    public void setDbPort(String dbPort) {
        this.dbPort = dbPort == null ? null : dbPort.trim();
    }

    public String getDbType() {
        return dbType;
    }

    public void setDbType(String dbType) {
        this.dbType = dbType == null ? null : dbType.trim();
    }

    public String getAppSystem() {
        return appSystem;
    }

    public void setAppSystem(String appSystem) {
        this.appSystem = appSystem == null ? null : appSystem.trim();
    }

    public Integer getDbStatus() {
        return dbStatus;
    }

    public void setDbStatus(Integer dbStatus) {
        this.dbStatus = dbStatus;
    }

    public String getDbUsername() {
        return dbUsername;
    }

    public void setDbUsername(String dbUsername) {
        this.dbUsername = dbUsername == null ? null : dbUsername.trim();
    }

    public String getDbPassword() {
        return dbPassword;
    }

    public void setDbPassword(String dbPassword) {
        this.dbPassword = dbPassword == null ? null : dbPassword.trim();
    }

	public String getDbOracleSid() {
		return dbOracleSid;
	}

	public void setDbOracleSid(String dbOracleSid) {
		this.dbOracleSid = dbOracleSid;
	}
}