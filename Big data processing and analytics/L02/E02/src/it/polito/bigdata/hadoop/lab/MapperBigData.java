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
class MapperBigData extends Mapper<
                    Text, // Input key type
                    Text,         // Input value type
                    IntWritable,         // Output key type
                    Text> {// Output value type
    
    protected void map(
            Text key,   // Input key type
            Text value,         // Input value type
            Context context) throws IOException, InterruptedException {
                IntWritable group;
                int occurences = Integer.parseInt(value.toString());
                if (occurences < 100) {
                    group = new IntWritable(0);
                }
                else if (occurences >= 100 && occurences < 200) {
                    group = new IntWritable(1);
                }
                else if (occurences >= 200 && occurences < 300) {
                    group = new IntWritable(2);
                }
                else if (occurences >= 300 && occurences < 400) {
                    group = new IntWritable(3);
                }
                else if (occurences >= 400 && occurences < 500) {
                    group = new IntWritable(4);
                }
                else {
                    group = new IntWritable(5);
                }
                context.write(group, key);
    }
}
