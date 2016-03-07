package com.itsm.datasource;

import org.apache.commons.dbcp.BasicDataSource;

import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.SQLFeatureNotSupportedException;
import java.util.logging.Logger;

/**
 * Created by CM on 2016/3/3.
 */
public class FixedBasicDataSource extends BasicDataSource {

    @Override
    public <T> T unwrap(Class<T> iface) throws SQLException {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public boolean isWrapperFor(Class<?> iface) throws SQLException {
        // TODO Auto-generated method stub
        return false;
    }
    @Override
    public synchronized void close() throws SQLException {
        DriverManager.deregisterDriver(DriverManager.getDriver(url));
        super.close();
    }

    @Override
    public Logger getParentLogger() throws SQLFeatureNotSupportedException {
        return null;
    }
}