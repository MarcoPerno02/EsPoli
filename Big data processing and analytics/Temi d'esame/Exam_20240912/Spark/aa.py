# Importiamo le librerie necessarie
from pyspark.sql import SparkSession
from pyspark.sql.types import StructType, StructField, StringType, IntegerType, DateType
from pyspark.sql.functions import col, year, sum, max

spark = SparkSession.builder.getOrCreate()
