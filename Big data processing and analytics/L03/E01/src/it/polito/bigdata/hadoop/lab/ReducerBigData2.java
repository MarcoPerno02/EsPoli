package it.polito.bigdata.hadoop.lab;

import java.io.IOException;
import java.util.Vector;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

/**
 * Lab - Reducer
 */

/* Set the proper data types for the (key,value) pairs */
class ReducerBigData2 extends Reducer<
                NullWritable,           // Input key type
                WordCountWritable,    // Input value type
                Text,           // Output key type
                IntWritable> {  // Output value type
    
    TopKVector<WordCountWritable> top3;
    
    protected void setup(Context context) {
        top3 = new TopKVector<WordCountWritable>(3);
    }

    @Override
    protected void reduce(
        NullWritable key, // Input key type
        Iterable<WordCountWritable> values, // Input value type
        Context context) throws IOException, InterruptedException {
            for(WordCountWritable tmp:values)
                top3.updateWithNewElement(new WordCountWritable(tmp.getWord(), tmp.getCount()));
                
            Vector<WordCountWritable> top3Objects = top3.getLocalTopK();

            for (WordCountWritable value : top3Objects) {
                context.write(new Text(value.getWord()), new IntWritable(value.getCount()));
            }
        }
}
