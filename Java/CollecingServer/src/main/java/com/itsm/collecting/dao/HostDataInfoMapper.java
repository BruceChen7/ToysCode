package com.itsm.collecting.dao;

import com.itsm.collecting.model.HostDataInfo;

public interface HostDataInfoMapper {
    int deleteByPrimaryKey(Integer hostId);

    int insert(HostDataInfo record);

    int insertSelective(HostDataInfo record);

    HostDataInfo selectByPrimaryKey(Integer hostId);

    int updateByPrimaryKeySelective(HostDataInfo record);

    int updateByPrimaryKey(HostDataInfo record);
}