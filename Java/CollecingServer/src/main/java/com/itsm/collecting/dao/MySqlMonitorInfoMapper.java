package com.itsm.collecting.dao;

import com.itsm.collecting.model.MySqlMonitorInfo;

public interface MySqlMonitorInfoMapper {
    int deleteByPrimaryKey(Long id);

    int insert(MySqlMonitorInfo record);

    int insertSelective(MySqlMonitorInfo record);

    MySqlMonitorInfo selectByPrimaryKey(Long id);

    int updateByPrimaryKeySelective(MySqlMonitorInfo record);

    int updateByPrimaryKey(MySqlMonitorInfo record);
}