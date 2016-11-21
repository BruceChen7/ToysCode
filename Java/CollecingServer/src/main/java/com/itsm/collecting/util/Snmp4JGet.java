package com.itsm.collecting.util;

import org.apache.log4j.Logger;
import org.snmp4j.CommunityTarget;
import org.snmp4j.PDU;
import org.snmp4j.Snmp;
import org.snmp4j.event.ResponseEvent;
import org.snmp4j.event.ResponseListener;
import org.snmp4j.smi.*;
import org.snmp4j.transport.DefaultUdpTransportMapping;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

public class Snmp4JGet {

	private static final Logger logger = Logger.getLogger(Snmp4JGet.class);

	private static Snmp4JGet snmp4jGet = new Snmp4JGet();

	public static Snmp4JGet getInstance() {
		if (snmp4jGet == null) {
			snmp4jGet = new Snmp4JGet();
		}
		return snmp4jGet;
	}
	/**
	 *  初始化CommunityTarget
	 * @param ip 远程计算机ip
	 * @param community 团体名称
	 * @return CommunityTarget对象实例
	 */
	public CommunityTarget createDefault(String ip , String community) {
		CommunityTarget target = new CommunityTarget();
		
		Address address = GenericAddress.parse(SnmpConstant.DEFAULT_PROTOCOL + ":" 
		+ ip + "/" + SnmpConstant.DEFAULT_PORT); 
		target.setCommunity(new OctetString(community));
		target.setAddress(address);
		target.setVersion(SnmpConstant.DEFAULT_VERSION);
		target.setTimeout(SnmpConstant.DEFAULT_TIMEOUT);
		target.setRetries(SnmpConstant.DEFAULT_RETRY);
		return target;
	}


	// 同步get一个oid
	/**
	 *  同步get一个oid对象实例
	 * @param ip 远程ip地址
	 * @param community 团体
	 * @param oidStr oid字符串
	 */
	public void snmpGet(String ip, String community, String oidStr) {
		CommunityTarget target = createDefault(ip, community);
		Snmp snmp = null;
		try {
			// 传输协议对象
			PDU pdu = new PDU();
			// MIB对象标识符
			OID oid = new OID(oidStr);
			// 绑定
			VariableBinding variableBinding = new VariableBinding(oid); 
			// 向pdu协议中放入绑定好的数据
			pdu.add(variableBinding);
			
			DefaultUdpTransportMapping transport = new DefaultUdpTransportMapping();
			// 创建snmp
			snmp = new Snmp(transport);

			// 监听数据传输
			snmp.listen();
			logger.info("--------发送PDU------------- ");
			// 设置pdu的类型
			pdu.setType(PDU.GET);
			// 发送pdu
			ResponseEvent respEvent  = snmp.send(pdu, target);
			
			logger.info("PeerAddress:" + respEvent.getPeerAddress());
			// 查看返回的PDU对象实例
			PDU response = respEvent.getResponse();
			
			if (response == null) {
				logger.error("response is null,request time out.");
			}
			else {
				logger.info("response pdu size is " + response.size());
				
				for (int i = 0; i < response.size(); i++) {
					VariableBinding vb = response.get(i);
					logger.info(vb.getOid() + "=" + vb.getVariable());
				}
			}
			
			logger.info("SNMP GET one OID value finished!");
		} catch (Exception e) {
			// TODO: handle exception
			logger.info(e.getStackTrace());
		} finally {
			if (snmp != null)
			{
				try {
                    logger.info("snmp close");
					snmp.close();
				} catch (Exception e2) {
					// TODO: handle exception
					logger.info(e2.getStackTrace());
					snmp = null;
				}
			}
		}
	}
	
	public List<VariableBinding> snmpGetList(String ip , String community, List<String> oidStrList) {
		// 初始化条件
		CommunityTarget target = createDefault(ip, community);
		Snmp snmp = null;
        List<VariableBinding> var_binding_list = new ArrayList<VariableBinding>();

		try {
			// 创建PDU对象实例
			PDU pdu = new PDU();
			// 绑定多个oid
			for(String oidStr:oidStrList)
			{
				OID oid = new OID(oidStr);
				VariableBinding vb = new VariableBinding(oid);
				pdu.add(vb);
			}
			DefaultUdpTransportMapping transportMapping = new DefaultUdpTransportMapping();

			snmp = new Snmp(transportMapping);
			snmp.listen();
			logger.info("-------------发送pdu消息---------");
			pdu.setType(PDU.GET);
			ResponseEvent respEvent = snmp.send(pdu, target);
			
			logger.info("PeerAddress:" + respEvent.getPeerAddress());
			PDU response =respEvent.getResponse();
			if(response == null) {
				logger.info("response is null,request time out.");
				
			}
			else {
				logger.info("response pdu size is:" + response.size());
				for (int i = 0; i < response.size(); i++) {
					VariableBinding vb = response.get(i);
                    var_binding_list.add(vb);
				}
			}
			logger.info("snmp get list oid value finished!");
            return var_binding_list;

		} catch (Exception e) {
			// TODO: handle exception
			logger.info(e.getStackTrace());
		} finally {
			if (snmp != null) {
				try {
					snmp.close();
				} catch (Exception e2) {
					// TODO: handle exception
					logger.info(e2.getStackTrace());
					snmp = null;
				}
			}
		}

        return var_binding_list;
	}


	/**
	 *  异步请求多个oid对象实例
	 * @param ip 远程计算机ip
	 * @param community 计算机团体名称
	 * @param oidStrList oid字符串集合
	 */
	public void snmpAsynGetList(String ip, String community, List<String> oidStrList) {
		CommunityTarget target = createDefault(ip, community);
		Snmp snmp = null;
		try {
			DefaultUdpTransportMapping transport = new DefaultUdpTransportMapping();
			snmp = new Snmp(transport);
			snmp.listen();
			PDU pdu = new PDU();
			for (String oidStr: oidStrList)
			{
				OID oid = new OID(oidStr);
				VariableBinding vb = new VariableBinding(oid);
				pdu.add(vb);
			}
			
			final CountDownLatch latch = new CountDownLatch(1);
			ResponseListener listener = new ResponseListener() {
				
				@Override
				public void onResponse(ResponseEvent event) {
					// TODO Auto-generated method stub
					((Snmp) event.getSource()).cancel(event.getRequest(), this);
					PDU response = event.getResponse();
					PDU request = event.getRequest();
					logger.info("[request]:" + request);
					if (response == null)
					{
						logger.error("[Error]:response is null");
					}
					else if(response.getErrorStatus() != 0)
					{
						logger.error("[Error]:repsonse status " + response.getErrorStatus() + 
								",Text:" + response.getErrorStatusText());
					}
					else {
						logger.info("Received response Succuss!response sise is " + response.size());
						for (int i = 0; i < response.size(); i++) {
							VariableBinding vb = response.get(i);
							logger.info(vb.getOid() + "=" + vb.getVariable());
						}
						logger.info("SNMP Asyn GetList OID finished!");
						latch.countDown();
					}
				}
			}; 
			pdu.setType(PDU.GET);
			snmp.send(pdu, target, null, listener);
			logger.info("Asyn send pdu wait for repsonse...");
			boolean wait = latch.await(30, TimeUnit.SECONDS);
			logger.info("latch.await = " + wait);
			snmp.close();
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
			logger.error(e);
		} 
	}
}
