package it.polito.bigdata.hadoop;

import java.io.IOException;
import java.util.ArrayList;

import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

/**
 * Basic MapReduce Project - Mapper
 */
class MapperBigData2 extends Mapper<Text, // Input key type
        Text, // Input value type
        NullWritable, // Output key type
        Text> {// Output value type


    protected void setup(Context context) {
    }

    protected void map(
            Text key, // Input key type
            Text value, // Input value type
            Context context) throws IOException, InterruptedException {


    }

    protected void cleanup(Context context) throws IOException, InterruptedException {
        
    }

}
