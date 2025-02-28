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
                    IntWritable> {// Output value type
    
    protected void map(
            LongWritable key,   // Input key type
            Text value,         // Input value type
            Context context) throws IOException, InterruptedException {

                String[] product_ids = value.toString().split(",");

                for (int i = 1; i < product_ids.length; i++) {
                    for (int j = i + 1; j < product_ids.length; j++) {
                        String pair;
                        if (product_ids[i].compareTo(product_ids[j]) == 1) {
                            pair = product_ids[i] + "," + product_ids[j];
                        }
                        else {
                            pair = product_ids[j] + "," + product_ids[i];
                        }
                            
                        context.write(new Text(pair), new IntWritable(1));
                    }
                }

    }
}
