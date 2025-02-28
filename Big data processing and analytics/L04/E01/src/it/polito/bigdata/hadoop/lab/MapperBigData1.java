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
                    ProductIdRatingWritable> {// Output value type
    
    protected void map(
            LongWritable key,   // Input key type
            Text value,         // Input value type
            Context context) throws IOException, InterruptedException {

    		String [] tmp = value.toString().split(",");

            if (tmp[0].compareTo("Id") != 0) {
                ProductIdRatingWritable productIdRating = new ProductIdRatingWritable(tmp[1], Integer.parseInt(tmp[6]));
                context.write(new Text(tmp[2]), productIdRating);
            }
    }
}
