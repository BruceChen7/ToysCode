package com.itsm.collecting.dao;

import com.itsm.collecting.model.MssqlBasicInfo;

public interface MssqlBasicInfoMapper {
    int deleteByPrimaryKey(Integer mssqlId);

    int insert(MssqlBasicInfo record);

    int insertSelective(MssqlBasicInfo record);

    MssqlBasicInfo selectByPrimaryKey(Integer mssqlId);

    int updateByPrimaryKeySelective(MssqlBasicInfo record);

    int updateByPrimaryKey(MssqlBasicInfo record);
}