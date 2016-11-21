package com.itsm.collecting.util;

import java.util.*;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

import org.apache.log4j.Logger;
import org.snmp4j.CommunityTarget;
import org.snmp4j.PDU;
import org.snmp4j.Snmp;
import org.snmp4j.TransportMapping;
import org.snmp4j.event.ResponseEvent;
import org.snmp4j.event.ResponseListener;
import org.snmp4j.smi.Integer32;
import org.snmp4j.smi.Null;
import org.snmp4j.smi.OID;
import org.snmp4j.smi.VariableBinding;
import org.snmp4j.transport.DefaultUdpTransportMapping;
import org.snmp4j.util.DefaultPDUFactory;
import org.snmp4j.util.PDUFactory;
import org.snmp4j.util.TableEvent;
import org.snmp4j.util.TableUtils;

public class Snmp4JGetWalk {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(Snmp4JGetWalk.class);

	private static Snmp4JGetWalk snmp4jGetWalk = new Snmp4JGetWalk();

    public static synchronized Snmp4JGetWalk getInstance() {
		if (snmp4jGetWalk == null)  {
			snmp4jGetWalk = new Snmp4JGetWalk();
		}
		return snmp4jGetWalk;
	}

	/**
	 *  同步walk访问mib
	 * @param ip 
	 * @param community
	 * @param oidStr
	 */
	public Map<String, VariableBinding> snmpWalk(String ip, String community, String oidStr) {
		CommunityTarget target = SnmpUtil.getInstance().createDefault(ip, community);
		TransportMapping transport = null;
		Snmp snmp = null;
        Map<String, VariableBinding> data = new HashMap<String, VariableBinding>();
        try {
			transport = new DefaultUdpTransportMapping();
			snmp = new Snmp(transport);
			snmp.listen();
			
			PDU pdu = new PDU();
			OID oid = new OID(oidStr);
			VariableBinding vb = new VariableBinding(oid);
			pdu.add(vb);
			boolean finished = false;
			logger.info("----demo start-------" + Thread.currentThread().getId());

            while (!finished)  {
				VariableBinding vbTemp = null;
				ResponseEvent respEvent = snmp.getNext(pdu, target);
				PDU response = respEvent.getResponse();

                if (response == null) {
                    logger.error("disk partition response is error ");
                    snmp.close();
                    break;
				}
				else  {
					vbTemp = response.get(0);
                    finished = checkWalkFinished(oid, pdu, vbTemp);
                    if (!finished) {
                        data.put(vbTemp.getOid().toString(), vbTemp);
                        pdu.setRequestID(new Integer32(0));
                        pdu.set(0, vbTemp);
                    } else {
                        snmp.close();
                    }
				}

			}
            logger.info("----demo end------" + Thread.currentThread().getId());
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
			logger.error("[Error:]" + e.getStackTrace().toString());
		} finally {
            return data;
        }

		
		
	}
	/**
	 *  检查是否访问完全
	 * @param oid 
	 * @param pdu
	 * @param vb
	 * @return
	 */
	private boolean checkWalkFinished(OID oid, PDU pdu, VariableBinding vb)
	{
		boolean finished = false;

        if (pdu.getErrorStatus() != 0)
		{
			logger.error("[true]:responsePDU.getErrorStatus() != 0 " + ",errorText=" + pdu.getErrorStatusText() );
			finished = true;			
		} else if(vb == null) {
            finished = true;
        } else if (vb.getOid() == null) {
			logger.error("[true]:vb == null");
			finished = true;
		}
		else if (vb.getOid().size() < oid.size())
		{
			logger.error("[true]:vb.getOid().size() < oid.size()");
			finished = true;
		}
		else if (oid.leftMostCompare(oid.size(), vb.getOid()) != 0)
		{
		   //  logger.error("[true]:oid.leftMostCompare(oid.size(), vb.getOid()) != 0");
			finished = true;
		}
		else if (Null.isExceptionSyntax(vb.getVariable().getSyntax()))
		{
			logger.error("[true]:Null.isExceptionSyntax(vb.getVariable().getSyntax())");
			finished = true;
		}
		else if (vb.getOid().compareTo(oid) <= 0)
		{
			logger.info("[true]:Varaible received is not"
					+"lexicographic successor of requested " + "one:");
			logger.info(vb.toString() + "<=" + oid);
			finished = true;
		}
		return finished;
	}
	/**
	 *  异步walk
	 * @param ip
	 * @param community
	 * @param oidStr
	 */
	public void snmpAsynWalk(String ip, String community, String oidStr) {
		final CommunityTarget target  = SnmpUtil.getInstance().createDefault(ip, community);
		Snmp snmp = null;
		try {
			logger.info("---- asyn walk start----");
			DefaultUdpTransportMapping transport = new DefaultUdpTransportMapping();
			snmp = new Snmp(transport);
			snmp.listen();
			
			final PDU pdu = new PDU();
			final OID oid = new OID(oidStr);
			VariableBinding requestVb = new VariableBinding(oid);
			pdu.add(requestVb);
			final CountDownLatch latch = new CountDownLatch(1);
			ResponseListener listener = new ResponseListener() {
				
				@Override
				public void onResponse(ResponseEvent event) {
					// TODO Auto-generated method stub
					((Snmp)event.getSource()).cancel(event.getRequest(), this);
					try {
						PDU response = event.getResponse();
						if (response == null)
						{
							logger.error("[Error]: response is null.");
						}
						else {
							logger.info("Received Walk response value :");
							VariableBinding vb = response.get(0);
							boolean finished = checkWalkFinished(oid, pdu, vb);
							if (!finished)
							{
								logger.info(vb.getOid() + "=" + vb.getVariable());
								pdu.setRequestID(new Integer32(0));
								pdu.set(0, vb);
								((Snmp)event.getSource()).getNext(pdu, target, null, this);
							}
							else {
								logger.info("SNMP Asyn Walk OID value success!");
								latch.countDown();
							}
						}
					} catch (Exception e) {
						// TODO: handle exception
						e.printStackTrace();
						latch.countDown();
					}
				}
			};
			
			snmp.getNext(pdu, target, null, listener);
			logger.info("pdu 已发送，等待异步处理结果...");
			
			boolean wait = latch.await(30, TimeUnit.SECONDS);
			logger.info("latch.await=:" + wait);
			snmp.close();
			
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
			logger.info("SNMP Asyn Walk Exception :" + e);
		}
	}
	
	public Map queryWalkTabData(String ip, String community,
			String... oidStrs)
	{
		Map result = null;
		SnmpUtil snmpUtil = SnmpUtil.getInstance();
	    snmpUtil.createDefault(ip, community, SnmpConstant.DEFAULT_VERSION);
		CommunityTarget target = snmpUtil.getTarget();
		Snmp snmp = snmpUtil.getSnmp();
		try {
			
			PDUFactory pf = new DefaultPDUFactory(PDU.GET);
			TableUtils tu = new TableUtils(snmp, pf);
			int oidSize = oidStrs.length;
			OID [] columns = new OID[oidSize];
			for (int i=0; i<oidStrs.length; i++)
			{
				columns[i] = new OID(oidStrs[i]);
			}
			//columns[0] = new VariableBinding(new OID(oidStr[0])).getOid();
			List<TableEvent> list = tu.getTable(target, columns, null, null);
			result = new LinkedHashMap<String,List<String>>();
			logger.info("------start walk---------");

			for (int i = 0; i < list.size(); i++) {
				
				TableEvent tb = list.get(i);
				VariableBinding[] vbs = tb.getColumns();
				if (vbs != null)
				{
					for (int j = 0; j < vbs.length; j++) {
						VariableBinding vb = vbs[j];
						OID oidStrTemp = vb.getOid();
						String value = vb.getVariable().toString();
						// logger.info(vb);
						//logger.info(vb.getVariable() + ":" + vb.getVariable().getSyntaxString());
						String processId = this.getProcessId(oidStrTemp.toString());
						List<String> dataList = this.getDataList(result, processId);
						dataList.add(value);
						
					}
				}
				else {
					logger.error("出现异常！");
				}
			}
            snmp.close();
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("queryTable is error ", e);
		}
        logger.info("---------end walk----------");
		return result;
				
	}
	/**
	 * 从oidStr中得到进程id
	 * @param oidStr 对象标识符字符串
	 * @return 对应的进程id
	 */
	public String getProcessId(String oidStr)
	{
		String tempOidStr = oidStr.trim();
		int pos = tempOidStr.lastIndexOf(".");
		String processId = tempOidStr.substring(pos + 1, tempOidStr.length());
		return processId;
	}
	/**
	 *  判断最终显示的map中是否包含了
	 * @param map 用户的map
	 * @param processId 进程id
	 * @return 进程id对应的list
	 */
	public List<String> getDataList(Map<String, List<String>> map, 
			String processId) {
		
		List<String> list = null;
		
		if (map.containsKey(processId))
		{
			list = (List)map.get(processId);
		}
		else {
			
			list = new LinkedList<String>();
			map.put(processId, list);
		}
		return list;
    }
}
