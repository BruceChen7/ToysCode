package com.itsm.collecting.util;

import org.snmp4j.CommunityTarget;
import org.snmp4j.Snmp;
import org.snmp4j.TransportMapping;
import org.snmp4j.smi.Address;
import org.snmp4j.smi.GenericAddress;
import org.snmp4j.smi.OctetString;
import org.snmp4j.transport.DefaultUdpTransportMapping;

import java.io.IOException;

public class SnmpUtil {

	private static SnmpUtil snmpUtil = new SnmpUtil();
	
    private CommunityTarget target;
	private Snmp snmp;

	public CommunityTarget getTarget() {
		return target;
	}
	public void setTarget(CommunityTarget target) {
		this.target = target;
	}
	public Snmp getSnmp() {
		return snmp;
	}
	public void setSnmp(Snmp snmp) {
		this.snmp = snmp;
	}

    public static SnmpUtil getInstance() {
		if (snmpUtil == null) {
			snmpUtil = new SnmpUtil();
		}
		return snmpUtil;
	}
	/**
	 *  初始化CommunityTarget
	 * @param ip 远程计算机ip
	 * @param community 团体名称
	 * @return CommunityTarget对象实例
	 */
	public CommunityTarget createDefault(String ip , String community) {
		target = new CommunityTarget();
		
		Address address = GenericAddress.parse(SnmpConstant.DEFAULT_PROTOCOL + ":" 
		+ ip + "/" + SnmpConstant.DEFAULT_PORT); 
		target.setCommunity(new OctetString(community));
		target.setAddress(address);
		target.setVersion(SnmpConstant.DEFAULT_VERSION);
		target.setTimeout(SnmpConstant.DEFAULT_TIMEOUT);
		target.setRetries(SnmpConstant.DEFAULT_RETRY);
		return target;
	}
	/**
	 *  初始化CommunityTarget
	 * @param ip 远程计算机ip
	 * @param community 团体名称
	 * @return CommunityTarget对象实例
	 */
	public void createDefault(String ip , String community,int version) {
		try {
			Address targetAddress = GenericAddress.parse("udp:" + ip + "/161");
			TransportMapping transport = new DefaultUdpTransportMapping();
			snmp = new Snmp(transport);
			// 璁剧疆target
			target = new CommunityTarget();
			target.setCommunity(new OctetString(community));
			target.setAddress(targetAddress);
			// 閫氫俊鎭笉鎴愬姛鏃堕噸璇曟鏁�
			target.setRetries(2);
			// 瓒呮椂鏃堕棿
			target.setTimeout(SnmpConstant.DEFAULT_TIMEOUT);
			target.setVersion(version);
			transport.listen();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
}
