package com.itsm.collecting.model;

public class Storage {

	private String hrStorageIndex;
	private String hrStorageType;
	private String hrStorageDescr;
	private float hrStorageAllocationUnits;
	private Double hrStorageSize;
	private double hrStorageUsed;
	private String hrStorageAllocationFailures;
	private double hrStorageUsedRate;
	private float hrStorageSpace;
	
	public String getHrStorageIndex() {
		return hrStorageIndex;
	}

	public void setHrStorageIndex(String hrStorageIndex) {
		this.hrStorageIndex = hrStorageIndex;
	}

	public String getHrStorageType() {
		return hrStorageType;
	}

	public void setHrStorageType(String hrStorageType) {
		this.hrStorageType = hrStorageType;
	}

	public String getHrStorageDescr() {
		return hrStorageDescr;
	}

	public void setHrStorageDescr(String hrStorageDescr) {
		this.hrStorageDescr = hrStorageDescr;
	}

	public float getHrStorageAllocationUnits() {
		return hrStorageAllocationUnits;
	}

	public void setHrStorageAllocationUnits(float hrStorageAllocationUnits) {
		this.hrStorageAllocationUnits = hrStorageAllocationUnits;
	}

	public double getHrStorageSize() {
		return hrStorageSize;
	}

	public void setHrStorageSize(double hrStorageSize) {
		this.hrStorageSize = hrStorageSize;
	}

	public double getHrStorageUsed() {
		return hrStorageUsed;
	}

	public void setHrStorageUsed(double hrStorageUsed) {
		this.hrStorageUsed = hrStorageUsed;
	}

	public String getHrStorageAllocationFailures() {
		return hrStorageAllocationFailures;
	}

	public void setHrStorageAllocationFailures(String hrStorageAllocationFailures) {
		this.hrStorageAllocationFailures = hrStorageAllocationFailures;
	}

	public double getHrStorageUsedRate() {
		return hrStorageUsedRate;
	}

	public void setHrStorageUsedRate(double hrStorageUsedRate) {
		this.hrStorageUsedRate = hrStorageUsedRate;
	}

	public float getHrStorageSpace() {
		return hrStorageSpace;
	}

	public void setHrStorageSpace(float hrStorageSpace) {
		this.hrStorageSpace = hrStorageSpace;
	}

	@Override
	public String toString() {
		return "Storage [hrStorageIndex=" + hrStorageIndex + ", hrStorageType="
				+ hrStorageType + ", hrStorageDescr=" + hrStorageDescr
				+ ", hrStorageAllocationUnits=" + hrStorageAllocationUnits
				+ ", hrStorageSize=" + hrStorageSize + ", hrStorageUsed="
				+ hrStorageUsed + ", hrStorageAllocationFailures="
				+ hrStorageAllocationFailures + ", hrStorageUsedRate="
				+ hrStorageUsedRate + ", hrStorageSpace=" + hrStorageSpace
				+ "]";
	}
	
}
