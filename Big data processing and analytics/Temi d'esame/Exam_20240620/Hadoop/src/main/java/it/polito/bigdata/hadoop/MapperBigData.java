package it.polito.bigdata.hadoop;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class MapperBigData extends Mapper<LongWritable, Text, Text, Offer> {

    @Override
    protected void map(LongWritable key, Text value, Context context)
            throws IOException, InterruptedException {
        String [] fields = value.toString().split(",");
        
        Offer offer = new Offer();
        offer.setSalary(Double.parseDouble(fields[2]));
        if(fields[3] == "Accepted")
            offer.setStatus(0);
        else {
            offer.setStatus(1);
        }
        
        context.write(new Text(fields[1]), offer);
        
    }

}
