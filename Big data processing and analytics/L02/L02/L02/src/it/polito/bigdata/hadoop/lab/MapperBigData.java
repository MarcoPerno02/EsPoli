package it.polito.bigdata.hadoop.lab;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

/**
 * Lab  - Mapper
 */

/* Set the proper data types for the (key,value) pairs */
class MapperBigData extends Mapper<
                    Text, // Input key type
                    Text,         // Input value type
                    Text,         // Output key type
                    IntWritable> {// Output value type
    
    protected void map(
            Text key,   // Input key type
            Text value,
            Context context) throws IOException, InterruptedException {
                if(key.toString().startsWith("ho")) {
                    Integer tmp = Integer.parseInt(value.toString());
                    context.write(key, new IntWritable(tmp));
                }
    }
}
