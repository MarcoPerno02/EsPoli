package it.polito.bigdata.hadoop;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

public class Offer implements org.apache.hadoop.io.Writable {

	private int status;
    private double salary;

    public double getSalary() {
        return salary;
    }

    public void setSalary(double salary) {
        this.salary = salary;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int accepted) {
        this.status = accepted;
    }

	@Override
	public void readFields(DataInput in) throws IOException {
		status = in.readInt();
        salary = in.readDouble();
	}

	@Override
	public void write(DataOutput out) throws IOException {
		out.writeInt(status);
        out.writeDouble(salary);
	}

}