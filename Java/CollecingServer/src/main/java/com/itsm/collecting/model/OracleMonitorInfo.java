package com.itsm.collecting.model;

public class OracleMonitorInfo {
    private Long id;

    private Integer dbId;

    private Integer sgaCacheHitrate;

    private Integer sgaDictionaryHitrate;

    private Integer sgaLibraryHitrate;

    private Integer sgaFreeMemSize;

    private Integer sgaBufferCacheSize;

    private Integer sgaSharedPoolSize;

    private Integer sgaLogBufferSize;

    private Integer sgaLibraryCacheSize;

    private Integer sgaDictionaryCacheSize;

    private Integer sgaSqlCacheSize;

    private Integer sgaSize;

    private Integer connectionTime;

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

    public Integer getSgaCacheHitrate() {
        return sgaCacheHitrate;
    }

    public void setSgaCacheHitrate(Integer sgaCacheHitrate) {
        this.sgaCacheHitrate = sgaCacheHitrate;
    }

    public Integer getSgaDictionaryHitrate() {
        return sgaDictionaryHitrate;
    }

    public void setSgaDictionaryHitrate(Integer sgaDictionaryHitrate) {
        this.sgaDictionaryHitrate = sgaDictionaryHitrate;
    }

    public Integer getSgaLibraryHitrate() {
        return sgaLibraryHitrate;
    }

    public void setSgaLibraryHitrate(Integer sgaLibraryHitrate) {
        this.sgaLibraryHitrate = sgaLibraryHitrate;
    }

    public Integer getSgaFreeMemSize() {
        return sgaFreeMemSize;
    }

    public void setSgaFreeMemSize(Integer sgaFreeMemSize) {
        this.sgaFreeMemSize = sgaFreeMemSize;
    }

    public Integer getSgaBufferCacheSize() {
        return sgaBufferCacheSize;
    }

    public void setSgaBufferCacheSize(Integer sgaBufferCacheSize) {
        this.sgaBufferCacheSize = sgaBufferCacheSize;
    }

    public Integer getSgaSharedPoolSize() {
        return sgaSharedPoolSize;
    }

    public void setSgaSharedPoolSize(Integer sgaSharedPoolSize) {
        this.sgaSharedPoolSize = sgaSharedPoolSize;
    }

    public Integer getSgaLogBufferSize() {
        return sgaLogBufferSize;
    }

    public void setSgaLogBufferSize(Integer sgaLogBufferSize) {
        this.sgaLogBufferSize = sgaLogBufferSize;
    }

    public Integer getSgaLibraryCacheSize() {
        return sgaLibraryCacheSize;
    }

    public void setSgaLibraryCacheSize(Integer sgaLibraryCacheSize) {
        this.sgaLibraryCacheSize = sgaLibraryCacheSize;
    }

    public Integer getSgaDictionaryCacheSize() {
        return sgaDictionaryCacheSize;
    }

    public void setSgaDictionaryCacheSize(Integer sgaDictionaryCacheSize) {
        this.sgaDictionaryCacheSize = sgaDictionaryCacheSize;
    }

    public Integer getSgaSqlCacheSize() {
        return sgaSqlCacheSize;
    }

    public void setSgaSqlCacheSize(Integer sgaSqlCacheSize) {
        this.sgaSqlCacheSize = sgaSqlCacheSize;
    }

    public Integer getSgaSize() {
        return sgaSize;
    }

    public void setSgaSize(Integer sgaSize) {
        this.sgaSize = sgaSize;
    }

    public Integer getConnectionTime() {
        return connectionTime;
    }

    public void setConnectionTime(Integer connectionTime) {
        this.connectionTime = connectionTime;
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
    	String monitor_data_string="";
    	if(this.sgaCacheHitrate!=null){
    		monitor_data_string=monitor_data_string+"sga_cache_hit_rate:"+this.sgaCacheHitrate;
    	}
    	else{
    		monitor_data_string=monitor_data_string+"sga_cache_hit_rate:0";
    	}
    	if(this.sgaDictionaryHitrate!=null){
    		monitor_data_string=monitor_data_string+"-sga_dictionary_hit_rate:"+this.sgaDictionaryHitrate;
    	}
    	else{
    		monitor_data_string=monitor_data_string+"-sga_dictionary_hit_rate:0";
    	}
    	if(this.sgaLibraryHitrate!=null){
    		monitor_data_string=monitor_data_string+"-sga_library_hit_rate:"+this.sgaLibraryHitrate;
    	}
    	else{
    		monitor_data_string=monitor_data_string+"-sga_library_hit_rate:0";
    	}
    	if(this.sgaFreeMemSize!=null){
    		monitor_data_string=monitor_data_string+"-sga_free_mem_size:"+this.sgaFreeMemSize;
    	}
    	else{
    		monitor_data_string=monitor_data_string+"-sga_free_mem_size:0";
    	}
    	if(this.sgaBufferCacheSize!=null){
    		monitor_data_string=monitor_data_string+"-sga_buffer_cache_size:"+this.sgaBufferCacheSize;
    	}
    	else{
    		monitor_data_string=monitor_data_string+"-sga_buffer_cache_size:0";
    	}
    	if(this.sgaSharedPoolSize!=null){
    		monitor_data_string=monitor_data_string+"-sga_shared_pool_size:"+this.sgaSharedPoolSize;
    	}
    	else{
    		monitor_data_string=monitor_data_string+"-sga_shared_pool_size:0";
    	}
    	if(this.sgaLogBufferSize!=null){
    		monitor_data_string=monitor_data_string+"-sga_log_buffer_size:"+this.sgaLogBufferSize;
    	}
    	else{
    		monitor_data_string=monitor_data_string+"-sga_log_buffer_size:0";
    	}
    	if(this.sgaLibraryCacheSize!=null){
    		monitor_data_string=monitor_data_string+"-sga_library_cache_size:"+this.sgaLibraryCacheSize;
    	}
    	else{
    		monitor_data_string=monitor_data_string+"-sga_library_cache_size:0";
    	}
    	if(this.sgaDictionaryCacheSize!=null){
    		monitor_data_string=monitor_data_string+"-sga_dictionary_cache_size:"+this.sgaDictionaryCacheSize;
    	}
    	else{
    		monitor_data_string=monitor_data_string+"-sga_dictionary_cache_size:0";
    	}
    	if(this.getSgaSqlCacheSize()!=null){
    		monitor_data_string=monitor_data_string+"-sga_sql_cache_size:"+this.sgaSqlCacheSize;
    	}
    	else{
    		monitor_data_string=monitor_data_string+"-sga_sql_cache_size:0";
    	}
    	if(this.sgaSize!=null){
    		monitor_data_string=monitor_data_string+"-sga_size:"+this.sgaSize;
    	}
    	else{
    		monitor_data_string=monitor_data_string+"-sga_size:0";
    	}
    	monitor_data_string=monitor_data_string+"-health_status:"+this.healthStatus;
    	monitor_data_string=monitor_data_string+"-health_status:0";
    	return monitor_data_string;
    }
}