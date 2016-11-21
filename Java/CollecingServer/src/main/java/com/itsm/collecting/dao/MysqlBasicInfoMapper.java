package com.itsm.collecting.dao;

import com.itsm.collecting.model.MysqlBasicInfo;

public interface MysqlBasicInfoMapper {
    int deleteByPrimaryKey(Integer mysqlId);

    int insert(MysqlBasicInfo record);

    int insertSelective(MysqlBasicInfo record);

    MysqlBasicInfo selectByPrimaryKey(Integer mysqlId);

    int updateByPrimaryKeySelective(MysqlBasicInfo record);

    int updateByPrimaryKey(MysqlBasicInfo record);
}