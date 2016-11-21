package com.itsm.collecting.dao;

import com.itsm.collecting.model.OracleBasicInfo;

public interface OracleBasicInfoMapper {
    int deleteByPrimaryKey(Integer oracleId);

    int insert(OracleBasicInfo record);

    int insertSelective(OracleBasicInfo record);

    OracleBasicInfo selectByPrimaryKey(Integer oracleId);

    int updateByPrimaryKeySelective(OracleBasicInfo record);

    int updateByPrimaryKey(OracleBasicInfo record);
}