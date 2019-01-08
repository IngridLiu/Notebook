# Spark数据读取与保存

<br>
<br>

## 1. 一般数据读取与保存功能

spark读取数据到DataFrame:

```scala
// load parquet file
// 以通用spark.read.load()形式读取parquet文件, 通用形式会自动识别path后缀
val usersDF = spark.read.load("path.parquet")
usersDF.select("name", "favorite_color").write.save("save_path.parquet")
// 以spark.read.parquet()形式读取parquet文件
val parquetFileDF = spark.read.parquet("people.parquet")

// load json file
// 以通用spark.read.load()形式读取json文件，标记format("json")
val usersDF = spark.read.format("json").load("path.json")
userDF.select("name", "age").write.format("parquet").save(save_path.parquet)
// 以spark.read.json()形式读取json文件
val peopleDF = spark.read.json("path.json")
peopleDF.write.parquet("people.parquet")

// load csv file
val peopleDFCsv = spark.read.format("csv")
  .option("sep", ",")
  .option("inferSchema", "true")
  .option("header", "true")
  .load("path.csv")
  
// 直接在parquet文件上运行SQL语句:
val sqlDF = spark.sql("SELECT * FROM parquet.`path.parquet`")
// 也可以对DataFrame创建一个视图，在视图上使用SQL
parquetFileDF.createOrReplaceTempView("parquetFile")
val namesDF = spark.sql("SELECT name FROM parquet File WHERE age BETWEEN 13 AND 19")
namesDF.map(attributes => "Name: " + attributes(0)).show()
// +------------+
// |       value|
// +------------+
// |Name: Justin|
// +------------+
```

Spark存储DataFrame:

```scala
// 将DataFrame存储为table,可以通过table访问；
peopleDF.write.bucketBy(42, "name").sortBy("age").saveAsTable("people_bucketed")    
// 将DataFrame存储为parquet
peopleDF.write.partitionBy("favorite_color").format("parquet").save("namesPartByColor.parquet") 
```

<br>
<br>
<br>
<br>

## Reference:

1.[Data Sources](http://spark.apache.org/docs/latest/sql-data-sources.html)

2.[Generic Load/Save Functions](http://spark.apache.org/docs/latest/sql-data-sources-load-save-functions.html)