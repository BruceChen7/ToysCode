package com.itsm.collecting.model;

/**
 * Created by CM on 2016/8/27.
 */
// 测试连接信息POJO
public class TestCollectingInfo {
    public String getOs() {
        return os;
    }

    public void setOs(String os) {
        this.os = os;
    }

    //
    private String os;

    public String getIp() {
        return ip;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }

    private String ip;

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    private String type;

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    private String userName;


    public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getPort() {
		return port;
	}

	public void setPort(String port) {
		this.port = port;
	}

	public String getSid() {
		return sid;
	}

	public void setSid(String sid) {
		this.sid = sid;
	}

	private String password;
	
	private int id;
	
	private String port;
	
	private String sid;
}
