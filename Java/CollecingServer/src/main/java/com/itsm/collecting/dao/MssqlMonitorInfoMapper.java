package com.itsm.collecting.dao;

import com.itsm.collecting.model.MssqlMonitorInfo;

public interface MssqlMonitorInfoMapper {
    int deleteByPrimaryKey(Long id);

    int insert(MssqlMonitorInfo record);

    int insertSelective(MssqlMonitorInfo record);

    MssqlMonitorInfo selectByPrimaryKey(Long id);

    int updateByPrimaryKeySelective(MssqlMonitorInfo record);

    int updateByPrimaryKey(MssqlMonitorInfo record);
}