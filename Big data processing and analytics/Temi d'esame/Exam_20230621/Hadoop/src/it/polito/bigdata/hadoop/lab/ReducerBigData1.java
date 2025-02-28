package it.polito.bigdata.hadoop.lab;

import java.io.IOException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;

import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

/**
 * Lab - Reducer
 */

/* Set the proper data types for the (key,value) pairs */
class ReducerBigData1 extends Reducer<
                Text,           // Input key type
                IntWritable,    // Input value type
                Text,           // Output key type
                NullWritable> {  // Output value type
    
    String max_mid;
    int max_value;

    @Override
    protected void setup(Context context) {
        max_mid = "";
        max_value = -1;
    }
    
    @Override
    protected void reduce(
        Text key, // Input key type
        Iterable<IntWritable> values, // Input value type
        Context context) throws IOException, InterruptedException {
        
        int accumulator = 0;
        for(IntWritable el:values) accumulator += el.get();

        if(accumulator > max_value || (accumulator == max_value && max_mid.compareTo(key.toString()) < 0)) {
            max_mid = key.toString();
            max_value = accumulator;
        }
      
    }

    @Override
    protected void cleanup(Context context) throws IOException, InterruptedException {
        context.write(new Text(max_mid), NullWritable.get());
    }
}
