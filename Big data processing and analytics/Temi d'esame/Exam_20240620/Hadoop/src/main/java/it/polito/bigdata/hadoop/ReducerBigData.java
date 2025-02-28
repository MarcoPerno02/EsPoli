package it.polito.bigdata.hadoop;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

/**
 * Basic MapReduce Project - Reducer
 */
class ReducerBigData extends Reducer<Text, // Input key type
        Offer, // Input value type
        Text, // Output key type
        IntWritable> { // Output value type

    @Override
    protected void reduce(
            Text key, // Input key type
            Iterable<Offer> values, // Input value type
            Context context) throws IOException, InterruptedException {
        Boolean valid = true;
        int countSalary = 0;

        for(Offer offer:values) {
            if(offer.getStatus() == 0) {
                valid = false;
                break;
            }
            if(offer.getSalary() > 100000) {
                countSalary++;
            }
        }

        if(valid && countSalary >= 10) {
                context.write(key, new IntWritable(countSalary));
        }
    }
}
