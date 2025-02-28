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
                NullWritable,    // Input value type
                IntWritable,           // Output key type
                NullWritable> {  // Output value type

    int accumulator;
    @Override
    protected void setup(Context context) {
        accumulator = 0;
    }

    @Override
    protected void reduce(
        Text key, // Input key type
        Iterable<NullWritable> values, // Input value type
        Context context) throws IOException, InterruptedException {
            accumulator++;
      
    }

    @Override
    protected void cleanup(Context context) throws IOException, InterruptedException {
        context.write(new IntWritable(accumulator), NullWritable.get());
    }
}
