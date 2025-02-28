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
                Text,    // Input value type
                Text,           // Output key type
                NullWritable> {  // Output value type
    
    @Override
    protected void reduce(
        Text key, // Input key type
        Iterable<Text> values, // Input value type
        Context context) throws IOException, InterruptedException {
        
            int acc_2020 = 0;
            int acc_2021 = 0;

            for(Text el:values) {
                String[] fields = el.toString().split(",");

                int year = Integer.parseInt(fields[0]);
                int kWh = Integer.parseInt(fields[1]);

                if(year == 2020)
                    acc_2020 += kWh;
                else
                    acc_2021 += kWh;
            }

            if(acc_2021 > acc_2020)
                context.write(key, NullWritable.get());
      
    }
}
