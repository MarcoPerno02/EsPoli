package it.polito.bigdata.hadoop.lab;

import java.io.IOException;

import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

/**
 * Lab - Reducer
 */

/* Set the proper data types for the (key,value) pairs */
class ReducerBigData2 extends Reducer<
                Text,           // Input key type
                IntWritable,    // Input value type
                Text,           // Output key type
                NullWritable> {  // Output value type
    
    String max_city = "";
    int max_value = -1;
    
    @Override
    protected void setup(Context context) {
        max_city = "";
        max_value = -1;
    }

    @Override
    protected void reduce(
        Text key, // Input key type
        Iterable<IntWritable> values, // Input value type
        Context context) throws IOException, InterruptedException {
        
            int accummulator = 0;
            for(IntWritable el:values) accummulator += el.get();

            if(accummulator > max_value || (accummulator == max_value && key.toString().compareTo(max_city) < 0)) {
                max_city = key.toString();
                max_value = accummulator;
            }
        
    }

    @Override
    protected void cleanup(Context context) throws IOException, InterruptedException {
        if(max_city.equals("") == false)
            context.write(new Text(max_city), NullWritable.get());
    }
}
