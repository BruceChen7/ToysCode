package com.itsm.collecting.dao;

import com.itsm.collecting.model.HostBasicInfo;

import java.util.List;

public interface HostBasicInfoMapper {
    int deleteByPrimaryKey(Integer hostId);

    int insert(HostBasicInfo record);

    int insertSelective(HostBasicInfo record);

    HostBasicInfo selectByPrimaryKey(Integer hostId);

    int updateByPrimaryKeySelective(HostBasicInfo record);

    int updateByPrimaryKey(HostBasicInfo record);

    List<HostBasicInfo> selectAllHost();

    List<HostBasicInfo> selectAllNeedToCollectHost();
}