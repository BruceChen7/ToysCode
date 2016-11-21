package com.itsm.collecting.model;

public class MssqlMonitorInfo {
    private Long id;

    private Integer dbId;

    private Integer totalMemory;

    private Integer sqlCachedMemory;

    private Integer lockedMemory;

    private Integer optimizedMemory;

    private Integer connectMemeory;

    private Integer executeProcessTotalMemory;

    private Integer waitWorkspaceProcessNum;

    private Integer getWorkspaceSuccessProcessNum;

    private Integer bufferHitRate;

    private Integer pageCheckNum;

    private Integer readPageNumPerMinute;

    private Integer writePageNumPerMinute;

    private Integer totalBufferPageNum;

    private Integer dbNum;

    private Integer freePageNum;

    private Integer connectionTime;

    private Integer connectionNum;

    private Integer loginNumPerMinute;

    private Integer logoutNumPerMinute;

    private Integer cacheHitRate;

    private Integer usedCachePerMinute;

    private Integer cacheCount;

    private Integer cachePageNum;

    private Integer lockRequestNumPerMinute;

    private Integer lockWaitTimePerMinute;

    private Integer lockTimeOutNumPerMinute;

    private Integer deadlockNumPerMinute;

    private Integer avgLockWaitTime;

    private Integer lotSizingRequestNumPerMinute;

    private Integer sqlCompileNumPerMinute;

    private Integer sqlRecompileNumPerMinute;

    private Integer autoParameterNumPerMinute;

    private Integer failAutoParameterNumPerMinute;

    private Integer consumeIoMost;

    private Integer consumeCpuMost;

    private Integer latchWaitNumPerMinute;

    private Integer avgLatchWaitTime;

    private Integer fullScanNumPerMinute;

    private Integer rangeScanNumPerMinute;

    private Integer probeScanNumPerMinute;

    private Integer dataFileSize;

    private Integer logFileSize;

    private String transactionDetail;

    private String logRefreshDetail;

    private Integer monitorTime;

    private Integer healthStatus;

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

    public Integer getTotalMemory() {
        return totalMemory;
    }

    public void setTotalMemory(Integer totalMemory) {
        this.totalMemory = totalMemory;
    }

    public Integer getSqlCachedMemory() {
        return sqlCachedMemory;
    }

    public void setSqlCachedMemory(Integer sqlCachedMemory) {
        this.sqlCachedMemory = sqlCachedMemory;
    }

    public Integer getLockedMemory() {
        return lockedMemory;
    }

    public void setLockedMemory(Integer lockedMemory) {
        this.lockedMemory = lockedMemory;
    }

    public Integer getOptimizedMemory() {
        return optimizedMemory;
    }

    public void setOptimizedMemory(Integer optimizedMemory) {
        this.optimizedMemory = optimizedMemory;
    }

    public Integer getConnectMemeory() {
        return connectMemeory;
    }

    public void setConnectMemeory(Integer connectMemeory) {
        this.connectMemeory = connectMemeory;
    }

    public Integer getExecuteProcessTotalMemory() {
        return executeProcessTotalMemory;
    }

    public void setExecuteProcessTotalMemory(Integer executeProcessTotalMemory) {
        this.executeProcessTotalMemory = executeProcessTotalMemory;
    }

    public Integer getWaitWorkspaceProcessNum() {
        return waitWorkspaceProcessNum;
    }

    public void setWaitWorkspaceProcessNum(Integer waitWorkspaceProcessNum) {
        this.waitWorkspaceProcessNum = waitWorkspaceProcessNum;
    }

    public Integer getGetWorkspaceSuccessProcessNum() {
        return getWorkspaceSuccessProcessNum;
    }

    public void setGetWorkspaceSuccessProcessNum(Integer getWorkspaceSuccessProcessNum) {
        this.getWorkspaceSuccessProcessNum = getWorkspaceSuccessProcessNum;
    }

    public Integer getBufferHitRate() {
        return bufferHitRate;
    }

    public void setBufferHitRate(Integer bufferHitRate) {
        this.bufferHitRate = bufferHitRate;
    }

    public Integer getPageCheckNum() {
        return pageCheckNum;
    }

    public void setPageCheckNum(Integer pageCheckNum) {
        this.pageCheckNum = pageCheckNum;
    }

    public Integer getReadPageNumPerMinute() {
        return readPageNumPerMinute;
    }

    public void setReadPageNumPerMinute(Integer readPageNumPerMinute) {
        this.readPageNumPerMinute = readPageNumPerMinute;
    }

    public Integer getWritePageNumPerMinute() {
        return writePageNumPerMinute;
    }

    public void setWritePageNumPerMinute(Integer writePageNumPerMinute) {
        this.writePageNumPerMinute = writePageNumPerMinute;
    }

    public Integer getTotalBufferPageNum() {
        return totalBufferPageNum;
    }

    public void setTotalBufferPageNum(Integer totalBufferPageNum) {
        this.totalBufferPageNum = totalBufferPageNum;
    }

    public Integer getDbNum() {
        return dbNum;
    }

    public void setDbNum(Integer dbNum) {
        this.dbNum = dbNum;
    }

    public Integer getFreePageNum() {
        return freePageNum;
    }

    public void setFreePageNum(Integer freePageNum) {
        this.freePageNum = freePageNum;
    }

    public Integer getConnectionTime() {
        return connectionTime;
    }

    public void setConnectionTime(Integer connectionTime) {
        this.connectionTime = connectionTime;
    }

    public Integer getConnectionNum() {
        return connectionNum;
    }

    public void setConnectionNum(Integer connectionNum) {
        this.connectionNum = connectionNum;
    }

    public Integer getLoginNumPerMinute() {
        return loginNumPerMinute;
    }

    public void setLoginNumPerMinute(Integer loginNumPerMinute) {
        this.loginNumPerMinute = loginNumPerMinute;
    }

    public Integer getLogoutNumPerMinute() {
        return logoutNumPerMinute;
    }

    public void setLogoutNumPerMinute(Integer logoutNumPerMinute) {
        this.logoutNumPerMinute = logoutNumPerMinute;
    }

    public Integer getCacheHitRate() {
        return cacheHitRate;
    }

    public void setCacheHitRate(Integer cacheHitRate) {
        this.cacheHitRate = cacheHitRate;
    }

    public Integer getUsedCachePerMinute() {
        return usedCachePerMinute;
    }

    public void setUsedCachePerMinute(Integer usedCachePerMinute) {
        this.usedCachePerMinute = usedCachePerMinute;
    }

    public Integer getCacheCount() {
        return cacheCount;
    }

    public void setCacheCount(Integer cacheCount) {
        this.cacheCount = cacheCount;
    }

    public Integer getCachePageNum() {
        return cachePageNum;
    }

    public void setCachePageNum(Integer cachePageNum) {
        this.cachePageNum = cachePageNum;
    }

    public Integer getLockRequestNumPerMinute() {
        return lockRequestNumPerMinute;
    }

    public void setLockRequestNumPerMinute(Integer lockRequestNumPerMinute) {
        this.lockRequestNumPerMinute = lockRequestNumPerMinute;
    }

    public Integer getLockWaitTimePerMinute() {
        return lockWaitTimePerMinute;
    }

    public void setLockWaitTimePerMinute(Integer lockWaitTimePerMinute) {
        this.lockWaitTimePerMinute = lockWaitTimePerMinute;
    }

    public Integer getLockTimeOutNumPerMinute() {
        return lockTimeOutNumPerMinute;
    }

    public void setLockTimeOutNumPerMinute(Integer lockTimeOutNumPerMinute) {
        this.lockTimeOutNumPerMinute = lockTimeOutNumPerMinute;
    }

    public Integer getDeadlockNumPerMinute() {
        return deadlockNumPerMinute;
    }

    public void setDeadlockNumPerMinute(Integer deadlockNumPerMinute) {
        this.deadlockNumPerMinute = deadlockNumPerMinute;
    }

    public Integer getAvgLockWaitTime() {
        return avgLockWaitTime;
    }

    public void setAvgLockWaitTime(Integer avgLockWaitTime) {
        this.avgLockWaitTime = avgLockWaitTime;
    }

    public Integer getLotSizingRequestNumPerMinute() {
        return lotSizingRequestNumPerMinute;
    }

    public void setLotSizingRequestNumPerMinute(Integer lotSizingRequestNumPerMinute) {
        this.lotSizingRequestNumPerMinute = lotSizingRequestNumPerMinute;
    }

    public Integer getSqlCompileNumPerMinute() {
        return sqlCompileNumPerMinute;
    }

    public void setSqlCompileNumPerMinute(Integer sqlCompileNumPerMinute) {
        this.sqlCompileNumPerMinute = sqlCompileNumPerMinute;
    }

    public Integer getSqlRecompileNumPerMinute() {
        return sqlRecompileNumPerMinute;
    }

    public void setSqlRecompileNumPerMinute(Integer sqlRecompileNumPerMinute) {
        this.sqlRecompileNumPerMinute = sqlRecompileNumPerMinute;
    }

    public Integer getAutoParameterNumPerMinute() {
        return autoParameterNumPerMinute;
    }

    public void setAutoParameterNumPerMinute(Integer autoParameterNumPerMinute) {
        this.autoParameterNumPerMinute = autoParameterNumPerMinute;
    }

    public Integer getFailAutoParameterNumPerMinute() {
        return failAutoParameterNumPerMinute;
    }

    public void setFailAutoParameterNumPerMinute(Integer failAutoParameterNumPerMinute) {
        this.failAutoParameterNumPerMinute = failAutoParameterNumPerMinute;
    }

    public Integer getConsumeIoMost() {
        return consumeIoMost;
    }

    public void setConsumeIoMost(Integer consumeIoMost) {
        this.consumeIoMost = consumeIoMost;
    }

    public Integer getConsumeCpuMost() {
        return consumeCpuMost;
    }

    public void setConsumeCpuMost(Integer consumeCpuMost) {
        this.consumeCpuMost = consumeCpuMost;
    }

    public Integer getLatchWaitNumPerMinute() {
        return latchWaitNumPerMinute;
    }

    public void setLatchWaitNumPerMinute(Integer latchWaitNumPerMinute) {
        this.latchWaitNumPerMinute = latchWaitNumPerMinute;
    }

    public Integer getAvgLatchWaitTime() {
        return avgLatchWaitTime;
    }

    public void setAvgLatchWaitTime(Integer avgLatchWaitTime) {
        this.avgLatchWaitTime = avgLatchWaitTime;
    }

    public Integer getFullScanNumPerMinute() {
        return fullScanNumPerMinute;
    }

    public void setFullScanNumPerMinute(Integer fullScanNumPerMinute) {
        this.fullScanNumPerMinute = fullScanNumPerMinute;
    }

    public Integer getRangeScanNumPerMinute() {
        return rangeScanNumPerMinute;
    }

    public void setRangeScanNumPerMinute(Integer rangeScanNumPerMinute) {
        this.rangeScanNumPerMinute = rangeScanNumPerMinute;
    }

    public Integer getProbeScanNumPerMinute() {
        return probeScanNumPerMinute;
    }

    public void setProbeScanNumPerMinute(Integer probeScanNumPerMinute) {
        this.probeScanNumPerMinute = probeScanNumPerMinute;
    }

    public Integer getDataFileSize() {
        return dataFileSize;
    }

    public void setDataFileSize(Integer dataFileSize) {
        this.dataFileSize = dataFileSize;
    }

    public Integer getLogFileSize() {
        return logFileSize;
    }

    public void setLogFileSize(Integer logFileSize) {
        this.logFileSize = logFileSize;
    }

    public String getTransactionDetail() {
        return transactionDetail;
    }

    public void setTransactionDetail(String transactionDetail) {
        this.transactionDetail = transactionDetail == null ? null : transactionDetail.trim();
    }

    public String getLogRefreshDetail() {
        return logRefreshDetail;
    }

    public void setLogRefreshDetail(String logRefreshDetail) {
        this.logRefreshDetail = logRefreshDetail == null ? null : logRefreshDetail.trim();
    }

    public Integer getMonitorTime() {
        return monitorTime;
    }

    public void setMonitorTime(Integer monitorTime) {
        this.monitorTime = monitorTime;
    }

    public Integer getHealthStatus() {
        return healthStatus;
    }

    public void setHealthStatus(Integer healthStatus) {
        this.healthStatus = healthStatus;
    }
    public String ObjectToString(){
    	String data_string = "";
    	if(this.totalMemory==null){
    		data_string = data_string + "Total_memory:0";
    	}
    	else{
    		data_string = data_string + "Total_memory:"+this.totalMemory;
    	}
    	if(this.sqlCachedMemory==null){
    		data_string = data_string + "-Sql_cached_memory:0";
    	}
    	else{
    		data_string = data_string + "-Sql_cached_memory:"+this.sqlCachedMemory;
    	}
    	if(this.lockedMemory==null){
    		data_string = data_string + "-Locked_memory:0";
    	}
    	else{
    		data_string = data_string + "-Locked_memory:"+this.lockedMemory;
    	}
    	if(this.optimizedMemory==null){
    		data_string = data_string + "-Optimized_memory:0";
    	}
    	else{
    		data_string = data_string + "-Optimized_memory:"+this.optimizedMemory;
    	}
    	if(this.connectMemeory==null){
    		data_string = data_string + "-Connect_memory:0";
    	}
    	else{
    		data_string = data_string + "-Connect_memory:"+ this.connectMemeory;
    	}
    	if(this.executeProcessTotalMemory==null){
    		data_string = data_string + "-Execute_process_total_memory:0";
    	}
    	else{
    		data_string = data_string + "-Execute_process_total_memory:"+this.executeProcessTotalMemory;
    	}
    	if(this.waitWorkspaceProcessNum==null){
    		data_string = data_string + "-Wait_work_space_process_num:0";
    	}
    	else{
    		data_string = data_string + "-Wait_work_space_process_num:"+this.waitWorkspaceProcessNum;
    	}
    	if(this.getWorkspaceSuccessProcessNum==null){
    		data_string = data_string + "-Get_work_space_process_num:0";
    	}
    	else{
    		data_string = data_string + "-Get_work_space_process_num:"+this.getWorkspaceSuccessProcessNum;
    	}
    	if(this.bufferHitRate==null){
    		data_string = data_string + "-Buffer_hit_rate:0";
    	}
    	else{
    		data_string = data_string + "-Buffer_hit_rate:"+this.bufferHitRate;
    	}
    	if(this.pageCheckNum==null){
    		data_string = data_string + "-Page_check_num:0";
    	}
    	else{
    		data_string = data_string + "-Page_check_num:"+this.pageCheckNum;
    	}
    	if(this.readPageNumPerMinute==null){
    		data_string = data_string + "-Read_page_num_per_min:0";
    	}
    	else{
    		data_string = data_string + "-Read_page_num_per_min:"+this.readPageNumPerMinute;
    	}
    	if(this.writePageNumPerMinute==null){
    		data_string = data_string + "-Write_page_num_per_min:0";
    	}
    	else{
    		data_string = data_string + "-Write_page_num_per_min:"+this.writePageNumPerMinute;
    	}
    	if(this.totalBufferPageNum==null){
    		data_string = data_string + "-Total_buffer_page_num:0";
    	}
    	else{
    		data_string = data_string + "-Total_buffer_page_num:"+this.totalBufferPageNum;
    	}
    	if(this.dbNum==null){
    		data_string = data_string + "-Db_page_num:0";
    	}
    	else{
    		data_string = data_string + "-Db_page_num:"+this.dbNum;
    	}
    	if(this.freePageNum==null){
    		data_string = data_string + "-Free_page_num:0";
    	}
    	else{
    		data_string = data_string + "-Free_page_num:"+this.freePageNum;
    	}
    	if(this.connectionTime==null){
    		data_string = data_string + "-Connection_time:0";
    	}
    	else{
    		data_string = data_string + "-Connection_time:"+this.connectionTime;
    	}
    	if(this.connectionNum==null){
    		data_string = data_string + "-Connection_num:0";
    	}
    	else{
    		data_string = data_string + "-Connection_num:"+this.connectionNum;
    	}
    	if(this.loginNumPerMinute==null){
    		data_string = data_string + "-Login_num_per_min:0";
    	}
    	else{
    		data_string = data_string + "-Login_num_per_min:"+this.loginNumPerMinute;
    	}
    	if(this.logoutNumPerMinute==null){
    		data_string = data_string + "-Logout_num_per_min:0";
    	}
    	else{
    		data_string = data_string + "-Logout_num_per_min:"+this.logoutNumPerMinute;
    	}
    	if(this.cacheHitRate==null){
    		data_string = data_string + "-Cache_hit_rate:0";
    	}
    	else{
    		data_string = data_string + "-Cache_hit_rate:"+this.cacheHitRate;
    	}
    	if(this.usedCachePerMinute==null){
    		data_string = data_string + "-Used_cache_per_min:0";
    	}
    	else{
    		data_string = data_string + "-Used_cache_per_min:"+this.usedCachePerMinute;
    	}
    	if(this.cacheCount==null){
    		data_string = data_string + "-Cache_count:0";
    	}
    	else{
    		data_string = data_string + "-Cache_count:"+this.cacheCount;
    	}
    	if(this.cachePageNum==null){
    		data_string = data_string + "-Cache_page_num:0";
    	}
    	else{
    		data_string = data_string + "-Cache_page_num:"+this.cachePageNum;
    	}
    	if(this.lockRequestNumPerMinute==null){
    		data_string = data_string + "-Lock_request_num_per_min:0";
    	}
    	else{
    		data_string = data_string + "-Lock_request_num_per_min:"+this.lockRequestNumPerMinute;
    	}
    	if(this.lockWaitTimePerMinute==null){
    		data_string = data_string + "-Lock_wait_time_per_min:0";
    	}
    	else{
    		data_string = data_string + "-Lock_wait_time_per_min:"+this.lockWaitTimePerMinute;
    	}
    	if(this.lockTimeOutNumPerMinute == null){
    		data_string = data_string + "-Lock_time_out_num_per_min:0";
    	}
    	else{
    		data_string = data_string + "-Lock_time_out_num_per_min:"+this.lockTimeOutNumPerMinute;
    	}
    	if(this.deadlockNumPerMinute==null){
    		data_string = data_string + "-Dead_lock_num_per_min:0";
    	}
    	else{
    		data_string = data_string + "-Dead_lock_num_per_min:"+this.deadlockNumPerMinute;
    	}
    	if(this.avgLockWaitTime==null){
    		data_string = data_string + "-Avg_lock_wait_time:0";
    	}
    	else{
    		data_string = data_string + "-Avg_lock_wait_time:"+this.avgLockWaitTime;
    	}
    	if(this.sqlCompileNumPerMinute==null){
    		data_string = data_string + "-Sql_complie_num_per_min:0";
    	}
    	else{
    		data_string = data_string + "-Sql_complie_num_per_min:"+this.sqlCompileNumPerMinute;
    	}
    	if(this.sqlRecompileNumPerMinute==null){
    		data_string = data_string + "-Sql_recomplie_num_per_min:0";
    	}
    	else{
    		data_string = data_string + "-Sql_recomplie_num_per_min:"+this.sqlRecompileNumPerMinute;
    	}
    	if(this.latchWaitNumPerMinute==null){
    		data_string = data_string + "-Latch_wait_num_per_min:0";
    	}
    	else{
    		data_string = data_string + "-Latch_wait_num_per_min:"+this.latchWaitNumPerMinute;
    	}
    	if(this.avgLatchWaitTime==null){
    		data_string = data_string + "-Avg_latch_wait_time:0";
    	}
    	else{
    		data_string = data_string + "-Avg_latch_wait_time:"+this.avgLatchWaitTime;
    	}
    	if(this.dataFileSize==null){
    		data_string = data_string + "-Data_file_size:0";
    	}
    	else{
    		data_string = data_string + "-Data_file_size:"+this.dataFileSize;
    	}
    	if(this.logFileSize==null){
    		data_string = data_string + "-Log_file_size:0";
    	}
    	else{
    		data_string = data_string + "-Log_file_size:"+this.logFileSize;
    	}
    	if(this.transactionDetail==null){
    		data_string = data_string + "-Transaction_detail:0";
    	}
    	else{
    		data_string = data_string + "-Transaction_detail:"+this.transactionDetail;
    	}
    	if(this.logRefreshDetail==null){
    		data_string = data_string + "-Log_refresh_detail:0";
    	}
    	else{
    		data_string = data_string + "-Log_refresh_detail:"+this.logRefreshDetail;
    	}
    	if(this.monitorTime==null){
    		data_string = data_string + "-Monitor_time:0";
    	}
    	else{
    		data_string = data_string + "-Monitor_time:"+this.monitorTime;
    	}
    	return data_string;
    }
}