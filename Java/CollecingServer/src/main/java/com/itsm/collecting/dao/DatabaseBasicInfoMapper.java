package com.itsm.collecting.dao;

import java.util.List;

import org.apache.ibatis.annotations.Param;

import com.itsm.collecting.model.DatabaseBasicInfo;

public interface DatabaseBasicInfoMapper {
    int deleteByPrimaryKey(Integer id);

    int insert(DatabaseBasicInfo record);

    int insertSelective(DatabaseBasicInfo record);

    DatabaseBasicInfo selectByPrimaryKey(Integer id);

    int updateByPrimaryKeySelective(DatabaseBasicInfo record);

    int updateByPrimaryKey(DatabaseBasicInfo record);


    List<DatabaseBasicInfo> selectAllDatabaseInUse();
    
    int selectByIpAndType(@Param("db_ip")String db_ip,@Param("db_type")String db_type);
}