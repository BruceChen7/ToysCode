package com.itsm.collecting.util;

import org.snmp4j.mp.SnmpConstants;

public class SnmpConstant {

	public static final int DEFAULT_VERSION = SnmpConstants.version2c;
	public static final String DEFAULT_PROTOCOL = "udp";
	public static final int DEFAULT_PORT = 161;
    public static final long DEFAULT_TIMEOUT = 1 * 1000L;
    public static final int DEFAULT_RETRY = 5;
    
}
