package com.itsm.collecting.dao;

import com.itsm.collecting.model.OracleMonitorInfo;

public interface OracleMonitorInfoMapper {
    int deleteByPrimaryKey(Long id);

    int insert(OracleMonitorInfo record);

    int insertSelective(OracleMonitorInfo record);

    OracleMonitorInfo selectByPrimaryKey(Long id);

    int updateByPrimaryKeySelective(OracleMonitorInfo record);

    int updateByPrimaryKey(OracleMonitorInfo record);
}