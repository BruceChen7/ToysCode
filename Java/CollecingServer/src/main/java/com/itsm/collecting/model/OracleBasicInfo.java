package com.itsm.collecting.model;

public class OracleBasicInfo {
    private Integer oracleId;

    private String oracleVersion;

    private Integer oracleStartTime;

    private Integer oracleFoundTime;

    private String oracleOpenType;

    private String oracleLogType;

    private Integer oracleSize;

    private Integer oracleReadNum;

    private Integer oracleWriteNum;

    private Integer oracleBlockSize;

    private String tablespaceName;

    private String tablespaceByteNum;

    private String tablesapceBlockNum;

    private String tablespaceFileNum;

    private String tablespaceStatus;

    private String tablespaceFreeByte;

    private String tablespaceFreeBlock;

    private String tablespaceReadNum;

    private String tablespaceWriteNum;

    private String tablespaceReadTime;

    private String tablespaceWriteTime;

    private String dataFileName;

    private String dataFileTablespace;

    private String dataFileStatus;

    private String dataFileCreateSize;

    private String dataFileReadNum;

    private String dataFileWriteNum;

    private String dataFileAvgReadTime;

    private String dataFileAvgWriteTime;

    private String sessionId;

    private String sessionStatus;

    private String sessionOutUserName;

    private String sessionDbUserName;

    private String sessionLogTime;

    private String sessionCpuUseTime;

    private String sessionMemorySize;

    private String sessionTableNum;

    private String sessionPhyreadNum;

    private String sessionLogireadNum;

    private String sessionSubmitNum;

    private String sessionCursorNum;

    private String sessionCacheHitRate;

    private String rollbackSegName;

    private String rollbackSegTablespace;

    private String rollbackSegStatus;

    private String rollbackSegCurrentSize;

    private String rollbackSegInitSize;

    private String rollbackSegNextSize;

    private String rollbackSegMinExtent;

    private String rollbackSegMaxExtent;

    private String rollbackSegHitRate;

    private String rollbackSegHwmsize;

    private String rollbackSegShrinks;

    private String rollbackSegWraps;

    private String rollbackSegExtends;

    public Integer getOracleId() {
        return oracleId;
    }

    public void setOracleId(Integer oracleId) {
        this.oracleId = oracleId;
    }

    public String getOracleVersion() {
        return oracleVersion;
    }

    public void setOracleVersion(String oracleVersion) {
        this.oracleVersion = oracleVersion == null ? null : oracleVersion.trim();
    }

    public Integer getOracleStartTime() {
        return oracleStartTime;
    }

    public void setOracleStartTime(Integer oracleStartTime) {
        this.oracleStartTime = oracleStartTime;
    }

    public Integer getOracleFoundTime() {
        return oracleFoundTime;
    }

    public void setOracleFoundTime(Integer oracleFoundTime) {
        this.oracleFoundTime = oracleFoundTime;
    }

    public String getOracleOpenType() {
        return oracleOpenType;
    }

    public void setOracleOpenType(String oracleOpenType) {
        this.oracleOpenType = oracleOpenType == null ? null : oracleOpenType.trim();
    }

    public String getOracleLogType() {
        return oracleLogType;
    }

    public void setOracleLogType(String oracleLogType) {
        this.oracleLogType = oracleLogType == null ? null : oracleLogType.trim();
    }

    public Integer getOracleSize() {
        return oracleSize;
    }

    public void setOracleSize(Integer oracleSize) {
        this.oracleSize = oracleSize;
    }

    public Integer getOracleReadNum() {
        return oracleReadNum;
    }

    public void setOracleReadNum(Integer oracleReadNum) {
        this.oracleReadNum = oracleReadNum;
    }

    public Integer getOracleWriteNum() {
        return oracleWriteNum;
    }

    public void setOracleWriteNum(Integer oracleWriteNum) {
        this.oracleWriteNum = oracleWriteNum;
    }

    public Integer getOracleBlockSize() {
        return oracleBlockSize;
    }

    public void setOracleBlockSize(Integer oracleBlockSize) {
        this.oracleBlockSize = oracleBlockSize;
    }

    public String getTablespaceName() {
        return tablespaceName;
    }

    public void setTablespaceName(String tablespaceName) {
        this.tablespaceName = tablespaceName == null ? null : tablespaceName.trim();
    }

    public String getTablespaceByteNum() {
        return tablespaceByteNum;
    }

    public void setTablespaceByteNum(String tablespaceByteNum) {
        this.tablespaceByteNum = tablespaceByteNum == null ? null : tablespaceByteNum.trim();
    }

    public String getTablesapceBlockNum() {
        return tablesapceBlockNum;
    }

    public void setTablesapceBlockNum(String tablesapceBlockNum) {
        this.tablesapceBlockNum = tablesapceBlockNum == null ? null : tablesapceBlockNum.trim();
    }

    public String getTablespaceFileNum() {
        return tablespaceFileNum;
    }

    public void setTablespaceFileNum(String tablespaceFileNum) {
        this.tablespaceFileNum = tablespaceFileNum == null ? null : tablespaceFileNum.trim();
    }

    public String getTablespaceStatus() {
        return tablespaceStatus;
    }

    public void setTablespaceStatus(String tablespaceStatus) {
        this.tablespaceStatus = tablespaceStatus == null ? null : tablespaceStatus.trim();
    }

    public String getTablespaceFreeByte() {
        return tablespaceFreeByte;
    }

    public void setTablespaceFreeByte(String tablespaceFreeByte) {
        this.tablespaceFreeByte = tablespaceFreeByte == null ? null : tablespaceFreeByte.trim();
    }

    public String getTablespaceFreeBlock() {
        return tablespaceFreeBlock;
    }

    public void setTablespaceFreeBlock(String tablespaceFreeBlock) {
        this.tablespaceFreeBlock = tablespaceFreeBlock == null ? null : tablespaceFreeBlock.trim();
    }

    public String getTablespaceReadNum() {
        return tablespaceReadNum;
    }

    public void setTablespaceReadNum(String tablespaceReadNum) {
        this.tablespaceReadNum = tablespaceReadNum == null ? null : tablespaceReadNum.trim();
    }

    public String getTablespaceWriteNum() {
        return tablespaceWriteNum;
    }

    public void setTablespaceWriteNum(String tablespaceWriteNum) {
        this.tablespaceWriteNum = tablespaceWriteNum == null ? null : tablespaceWriteNum.trim();
    }

    public String getTablespaceReadTime() {
        return tablespaceReadTime;
    }

    public void setTablespaceReadTime(String tablespaceReadTime) {
        this.tablespaceReadTime = tablespaceReadTime == null ? null : tablespaceReadTime.trim();
    }

    public String getTablespaceWriteTime() {
        return tablespaceWriteTime;
    }

    public void setTablespaceWriteTime(String tablespaceWriteTime) {
        this.tablespaceWriteTime = tablespaceWriteTime == null ? null : tablespaceWriteTime.trim();
    }

    public String getDataFileName() {
        return dataFileName;
    }

    public void setDataFileName(String dataFileName) {
        this.dataFileName = dataFileName == null ? null : dataFileName.trim();
    }

    public String getDataFileTablespace() {
        return dataFileTablespace;
    }

    public void setDataFileTablespace(String dataFileTablespace) {
        this.dataFileTablespace = dataFileTablespace == null ? null : dataFileTablespace.trim();
    }

    public String getDataFileStatus() {
        return dataFileStatus;
    }

    public void setDataFileStatus(String dataFileStatus) {
        this.dataFileStatus = dataFileStatus == null ? null : dataFileStatus.trim();
    }

    public String getDataFileCreateSize() {
        return dataFileCreateSize;
    }

    public void setDataFileCreateSize(String dataFileCreateSize) {
        this.dataFileCreateSize = dataFileCreateSize == null ? null : dataFileCreateSize.trim();
    }

    public String getDataFileReadNum() {
        return dataFileReadNum;
    }

    public void setDataFileReadNum(String dataFileReadNum) {
        this.dataFileReadNum = dataFileReadNum == null ? null : dataFileReadNum.trim();
    }

    public String getDataFileWriteNum() {
        return dataFileWriteNum;
    }

    public void setDataFileWriteNum(String dataFileWriteNum) {
        this.dataFileWriteNum = dataFileWriteNum == null ? null : dataFileWriteNum.trim();
    }

    public String getDataFileAvgReadTime() {
        return dataFileAvgReadTime;
    }

    public void setDataFileAvgReadTime(String dataFileAvgReadTime) {
        this.dataFileAvgReadTime = dataFileAvgReadTime == null ? null : dataFileAvgReadTime.trim();
    }

    public String getDataFileAvgWriteTime() {
        return dataFileAvgWriteTime;
    }

    public void setDataFileAvgWriteTime(String dataFileAvgWriteTime) {
        this.dataFileAvgWriteTime = dataFileAvgWriteTime == null ? null : dataFileAvgWriteTime.trim();
    }

    public String getSessionId() {
        return sessionId;
    }

    public void setSessionId(String sessionId) {
        this.sessionId = sessionId == null ? null : sessionId.trim();
    }

    public String getSessionStatus() {
        return sessionStatus;
    }

    public void setSessionStatus(String sessionStatus) {
        this.sessionStatus = sessionStatus == null ? null : sessionStatus.trim();
    }

    public String getSessionOutUserName() {
        return sessionOutUserName;
    }

    public void setSessionOutUserName(String sessionOutUserName) {
        this.sessionOutUserName = sessionOutUserName == null ? null : sessionOutUserName.trim();
    }

    public String getSessionDbUserName() {
        return sessionDbUserName;
    }

    public void setSessionDbUserName(String sessionDbUserName) {
        this.sessionDbUserName = sessionDbUserName == null ? null : sessionDbUserName.trim();
    }

    public String getSessionLogTime() {
        return sessionLogTime;
    }

    public void setSessionLogTime(String sessionLogTime) {
        this.sessionLogTime = sessionLogTime == null ? null : sessionLogTime.trim();
    }

    public String getSessionCpuUseTime() {
        return sessionCpuUseTime;
    }

    public void setSessionCpuUseTime(String sessionCpuUseTime) {
        this.sessionCpuUseTime = sessionCpuUseTime == null ? null : sessionCpuUseTime.trim();
    }

    public String getSessionMemorySize() {
        return sessionMemorySize;
    }

    public void setSessionMemorySize(String sessionMemorySize) {
        this.sessionMemorySize = sessionMemorySize == null ? null : sessionMemorySize.trim();
    }

    public String getSessionTableNum() {
        return sessionTableNum;
    }

    public void setSessionTableNum(String sessionTableNum) {
        this.sessionTableNum = sessionTableNum == null ? null : sessionTableNum.trim();
    }

    public String getSessionPhyreadNum() {
        return sessionPhyreadNum;
    }

    public void setSessionPhyreadNum(String sessionPhyreadNum) {
        this.sessionPhyreadNum = sessionPhyreadNum == null ? null : sessionPhyreadNum.trim();
    }

    public String getSessionLogireadNum() {
        return sessionLogireadNum;
    }

    public void setSessionLogireadNum(String sessionLogireadNum) {
        this.sessionLogireadNum = sessionLogireadNum == null ? null : sessionLogireadNum.trim();
    }

    public String getSessionSubmitNum() {
        return sessionSubmitNum;
    }

    public void setSessionSubmitNum(String sessionSubmitNum) {
        this.sessionSubmitNum = sessionSubmitNum == null ? null : sessionSubmitNum.trim();
    }

    public String getSessionCursorNum() {
        return sessionCursorNum;
    }

    public void setSessionCursorNum(String sessionCursorNum) {
        this.sessionCursorNum = sessionCursorNum == null ? null : sessionCursorNum.trim();
    }

    public String getSessionCacheHitRate() {
        return sessionCacheHitRate;
    }

    public void setSessionCacheHitRate(String sessionCacheHitRate) {
        this.sessionCacheHitRate = sessionCacheHitRate == null ? null : sessionCacheHitRate.trim();
    }

    public String getRollbackSegName() {
        return rollbackSegName;
    }

    public void setRollbackSegName(String rollbackSegName) {
        this.rollbackSegName = rollbackSegName == null ? null : rollbackSegName.trim();
    }

    public String getRollbackSegTablespace() {
        return rollbackSegTablespace;
    }

    public void setRollbackSegTablespace(String rollbackSegTablespace) {
        this.rollbackSegTablespace = rollbackSegTablespace == null ? null : rollbackSegTablespace.trim();
    }

    public String getRollbackSegStatus() {
        return rollbackSegStatus;
    }

    public void setRollbackSegStatus(String rollbackSegStatus) {
        this.rollbackSegStatus = rollbackSegStatus == null ? null : rollbackSegStatus.trim();
    }

    public String getRollbackSegCurrentSize() {
        return rollbackSegCurrentSize;
    }

    public void setRollbackSegCurrentSize(String rollbackSegCurrentSize) {
        this.rollbackSegCurrentSize = rollbackSegCurrentSize == null ? null : rollbackSegCurrentSize.trim();
    }

    public String getRollbackSegInitSize() {
        return rollbackSegInitSize;
    }

    public void setRollbackSegInitSize(String rollbackSegInitSize) {
        this.rollbackSegInitSize = rollbackSegInitSize == null ? null : rollbackSegInitSize.trim();
    }

    public String getRollbackSegNextSize() {
        return rollbackSegNextSize;
    }

    public void setRollbackSegNextSize(String rollbackSegNextSize) {
        this.rollbackSegNextSize = rollbackSegNextSize == null ? null : rollbackSegNextSize.trim();
    }

    public String getRollbackSegMinExtent() {
        return rollbackSegMinExtent;
    }

    public void setRollbackSegMinExtent(String rollbackSegMinExtent) {
        this.rollbackSegMinExtent = rollbackSegMinExtent == null ? null : rollbackSegMinExtent.trim();
    }

    public String getRollbackSegMaxExtent() {
        return rollbackSegMaxExtent;
    }

    public void setRollbackSegMaxExtent(String rollbackSegMaxExtent) {
        this.rollbackSegMaxExtent = rollbackSegMaxExtent == null ? null : rollbackSegMaxExtent.trim();
    }

    public String getRollbackSegHitRate() {
        return rollbackSegHitRate;
    }

    public void setRollbackSegHitRate(String rollbackSegHitRate) {
        this.rollbackSegHitRate = rollbackSegHitRate == null ? null : rollbackSegHitRate.trim();
    }

    public String getRollbackSegHwmsize() {
        return rollbackSegHwmsize;
    }

    public void setRollbackSegHwmsize(String rollbackSegHwmsize) {
        this.rollbackSegHwmsize = rollbackSegHwmsize == null ? null : rollbackSegHwmsize.trim();
    }

    public String getRollbackSegShrinks() {
        return rollbackSegShrinks;
    }

    public void setRollbackSegShrinks(String rollbackSegShrinks) {
        this.rollbackSegShrinks = rollbackSegShrinks == null ? null : rollbackSegShrinks.trim();
    }

    public String getRollbackSegWraps() {
        return rollbackSegWraps;
    }

    public void setRollbackSegWraps(String rollbackSegWraps) {
        this.rollbackSegWraps = rollbackSegWraps == null ? null : rollbackSegWraps.trim();
    }

    public String getRollbackSegExtends() {
        return rollbackSegExtends;
    }

    public void setRollbackSegExtends(String rollbackSegExtends) {
        this.rollbackSegExtends = rollbackSegExtends == null ? null : rollbackSegExtends.trim();
    }
}