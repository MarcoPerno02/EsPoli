package it.polito.bigdata.hadoop.lab;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

/**
 * Lab  - Mapper
 */

/* Set the proper data types for the (key,value) pairs */
class MapperBigData1 extends Mapper<
                    LongWritable, // Input key type
                    Text,         // Input value type
                    Text,         // Output key type
                    Text> {// Output value type
    
    protected void map(
            LongWritable key,   // Input key type
            Text value,         // Input value type
            Context context) throws IOException, InterruptedException {

    	String [] fields = value.toString().split(",");
        int year = Integer.parseInt(fields[1].split("/")[0]);
        int kWh = Integer.parseInt(fields[2]);

        if((year == 2020 || year == 2021) && kWh > 1000)
                context.write(new Text(fields[0]), new Text(Integer.toString(year) + "," + Integer.toString(kWh)));

    }
}
