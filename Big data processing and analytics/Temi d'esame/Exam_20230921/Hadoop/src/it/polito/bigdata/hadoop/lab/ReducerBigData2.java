package it.polito.bigdata.hadoop.lab;

import java.io.IOException;

import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

/**
 * Lab - Reducer
 */

/* Set the proper data types for the (key,value) pairs */
class ReducerBigData2 extends Reducer<
                Text,           // Input key type
                Text,    // Input value type
                Text,           // Output key type
                Text> {  // Output value type
    
    @Override
    protected void reduce(
        Text key, // Input key type
        Iterable<Text> values, // Input value type
        Context context) throws IOException, InterruptedException {

		int long_accumulator = 0;
        int short_accumulator = 0;

        for(Text el:values) {
            if(el.toString().equals("Long")) {
                long_accumulator++;
            }
            else {
                short_accumulator++;
            }
        }

        context.write(key, new Text(Integer.toString(long_accumulator) + " " + Integer.toString(short_accumulator)));
    	
    }
}
