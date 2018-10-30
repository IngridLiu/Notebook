# Hive学习笔记

<br>
<br>
<br>
<br>

## 1 Hive对数据库的操作

### 1.1 Hive对表的操作

### 1.1.1 CREATE TABLE语句

**语法**

```
CREATE [TEMPORARY] [EXTERNAL] TABLE [IF NOT EXISTS] [db_name.] table_name

[(col_name data_type [COMMENT col_comment], ...)]
[COMMENT table_comment]
[ROW FORMAT row_format]
[STORED AS file_format]

```

**示例**

```
CREATE TABLE IF NOT EXISTS employee ( eid int, name String,
salary String, destination String)
COMMENT ‘Employee details’
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ‘\t’
LINES TERMINATED BY ‘\n’
STORED AS TEXTFILE;
```

### 1.1.2 ALTER TABLE 语句

**语法**

```
ALTER TABLE name RENAME TO new_name
ALTER TABLE name ADD COLUMNS (col_spec[, col_spec ...])
ALTER TABLE name DROP [COLUMN] column_name
ALTER TABLE name CHANGE column_name new_name new_type
ALTER TABLE name REPLACE COLUMNS (col_spec[, col_spec ...])
```

**示例**

```
ALTER TABLE employee RENAME TO emp;
```

### 1.1.3 DROP TABLE 语句

**语法**

```
DROP TABLE [IF EXISTS] table_name;
```

**示例**

```
DROP TABLE IF EXISTS employee;
```


<br>
<br>

## 2 Hive 数据导入导出

### 2.1 Hive数据导入

&emsp;&emsp;总结Hive的几种常见的数据导入方式，总结为四种：

&emsp;&emsp;（1）从本地文件系统中导入数据到Hive表；

&emsp;&emsp;（2）从HDFS上导入数据到Hive表；

&emsp;&emsp;（3）从别的表中查询出相应的数据并导入到Hive表中；

&emsp;&emsp;（4）在创建表的时候通过从别的表中查询出相应的记录并插入到所创建的表中。

### 2.1.1 从本地文件系统中导入数据到Hive表

&emsp;&emsp;先在Hive里面创建好表，如下：

```bash
hive> create table wyp
    > (id int, name string,
    > age int, tel string)
    > ROW FORMAT DELIMITED
    > FIELDS TERMINATED BY '\t'
    > STORED AS TEXTFILE;
OK
Time taken: 2.832 seconds
```

&emsp;&emsp;这个表很简单，只有四个字段，具体含义我就不解释了。本地文件系统里面有个 /home/wyp/wyp.txt 文件，内容如下：

```bash
[wyp@master ~]$ cat wyp.txt
1       wyp     25      13188888888888
2       test    30      13888888888888
3       zs      34      899314121
```

&emsp;&emsp;wyp.txt文件中的数据列之间是使用 \t 分割的，可以通过下面的语句将这个文件里面的数据导入到wyp表里面，操作如下：

```bash
hive> load data local inpath 'wyp.txt' into table wyp;
Copying data from file:/home/wyp/wyp.txt
Copying file: file:/home/wyp/wyp.txt
Loading data to table default.wyp
Table default.wyp stats:
[num_partitions: 0, num_files: 1, num_rows: 0, total_size: 67]
OK
Time taken: 5.967 seconds
```

&emsp;&emsp;这样就将wyp.txt里面的内容导入到wyp表里面去了（关于这里面的执行过程大家可以参见本博客的《Hive表与外部表》），可以到wyp表的数据目录下查看，如下命令：

```bash
hive> dfs -ls /user/hive/warehouse/wyp ;
Found 1 items
-rw-r--r--3 wyp supergroup 67 2014-02-19 18:23 /hive/warehouse/wyp/wyp.txt
```

&emsp;&emsp;数据的确导入到wyp表里面去了。

> 和我们熟悉的关系型数据库不一样，Hive现在还不支持在insert语句里面直接给出一组记录的文字形式，也就是说，Hive并不支持INSERT INTO .... VALUES形式的语句。

#### 2.1.2 HDFS上导入数据到Hive表

&emsp;&emsp;从本地文件系统中将数据导入到Hive表的过程中，其实是先将数据临时复制到HDFS的一个目录下（典型的情况是复制到上传用户的HDFS home目录下,比如/home/wyp/），然后再将数据从那个临时目录下移动（注意，这里说的是移动，不是复制！）到对应的Hive表的数据目录里面。既然如此，那么Hive肯定支持将数据直接从HDFS上的一个目录移动到相应Hive表的数据目录下，假设有下面这个文件/home/wyp/add.txt，具体的操作如下：

```bash
[wyp@master /home/q/hadoop-2.2.0]$ bin/hadoop fs -cat /home/wyp/add.txt
5       wyp1    23      131212121212
6       wyp2    24      134535353535
7       wyp3    25      132453535353
8       wyp4    26      154243434355
```

&emsp;&emsp;上面是需要插入数据的内容，这个文件是存放在HDFS上/home/wyp目录（和一中提到的不同，一中提到的文件是存放在本地文件系统上）里面，我们可以通过下面的命令将这个文件里面的内容导入到Hive表中，具体操作如下：

```bash
hive> load data inpath '/home/wyp/add.txt' into table wyp;
Loading data to table default.wyp
Table default.wyp stats:
[num_partitions: 0, num_files: 2, num_rows: 0, total_size: 215]
OK
Time taken: 0.47 seconds
 
hive> select * from wyp;
OK
5       wyp1    23      131212121212
6       wyp2    24      134535353535
7       wyp3    25      132453535353
8       wyp4    26      154243434355
1       wyp     25      13188888888888
2       test    30      13888888888888
3       zs      34      899314121
Time taken: 0.096 seconds, Fetched: 7 row(s)
```

&emsp;&emsp;从上面的执行结果我们可以看到，数据的确导入到wyp表中了！请注意load data inpath '/home/wyp/add.txt' into table wyp;里面是没有local这个单词的，这个是和一中的区别。

#### 2.1.3 从别的表中查询出相应的数据并导入到Hive表中

&emsp;&emsp;假设Hive中有test表，其建表语句如下所示：

&emsp;&emsp;大体和wyp表的建表语句类似，只不过test表里面用age作为了分区字段客。下面语句就是将wyp表中的查询结果并插入到test表中：

```bash
hive> insert into table test
    > partition (age='25')
    > select id, name, tel
    > from wyp;
#####################################################################
           这里输出了一堆Mapreduce任务信息，这里省略
#####################################################################
Total MapReduce CPU Time Spent: 1 seconds 310 msec
OK
Time taken: 19.125 seconds
 
hive> select * from test;
OK
5       wyp1    131212121212    25
6       wyp2    134535353535    25
7       wyp3    132453535353    25
8       wyp4    154243434355    25
1       wyp     13188888888888  25
2       test    13888888888888  25
3       zs      899314121       25
Time taken: 0.126 seconds, Fetched: 7 row(s)
```

&emsp;&emsp;通过上面的输出，我们可以看到从wyp表中查询出来的东西已经成功插入到test表中去了！如果目标表（test）中不存在分区字段，可以去掉partition (age='25')语句。当然，我们也可以在select语句里面通过使用分区值来动态指明分区：

```bash
hive> set hive.exec.dynamic.partition.mode=nonstrict;
hive> insert into table test
    > partition (age)
    > select id, name,
    > tel, age
    > from wyp;
#####################################################################
           这里输出了一堆Mapreduce任务信息，这里省略
#####################################################################
Total MapReduce CPU Time Spent: 1 seconds 510 msec
OK
Time taken: 17.712 seconds
 
 
hive> select * from test;
OK
5       wyp1    131212121212    23
6       wyp2    134535353535    24
7       wyp3    132453535353    25
1       wyp     13188888888888  25
8       wyp4    154243434355    26
2       test    13888888888888  30
3       zs      899314121       34
Time taken: 0.399 seconds, Fetched: 7 row(s)
```

&emsp;&emsp;这种方法叫做动态分区插入，但是Hive中默认是关闭的，所以在使用前需要先把hive.exec.dynamic.partition.mode设置为nonstrict。当然，Hive也支持insert overwrite方式来插入数据，从字面我们就可以看出，overwrite是覆盖的意思，是的，执行完这条语句的时候，相应数据目录下的数据将会被覆盖！而insert into则不会，注意两者之间的区别。例子如下：


```bash
hive> insert overwrite table test
    > PARTITION (age)
    > select id, name, tel, age
    > from wyp;
```

&emsp;&emsp;更可喜的是，Hive还支持多表插入，什么意思呢？在Hive中，我们可以把insert语句倒过来，把from放在最前面，它的执行效果和放在后面是一样的，如下：

```bash
hive> show create table test3;
OK
CREATE  TABLE test3(
  id int,
  name string)
Time taken: 0.277 seconds, Fetched: 18 row(s)
 
hive> from wyp
    > insert into table test
    > partition(age)
    > select id, name, tel, age
    > insert into table test3
    > select id, name
    > where age>25;
 
hive> select * from test3;
OK
8       wyp4
2       test
3       zs
Time taken: 4.308 seconds, Fetched: 3 row(s)
```

&emsp;&emsp;可以在同一个查询中使用多个insert子句，这样的好处是我们只需要扫描一遍源表就可以生成多个不相交的输出。

#### 2.1.4 在创建表的时候通过从别的表中查询出相应的记录并插入到所创建的表中

&emsp;&emsp;在实际情况中，表的输出结果可能太多，不适于显示在控制台上，这时候，将Hive的查询输出结果直接存在一个新的表中是非常方便的，我们称这种情况为CTAS（create table .. as select）如下：

```bash
hive> create table test4
    > as
    > select id, name, tel
    > from wyp;
 
hive> select * from test4;
OK
5       wyp1    131212121212
6       wyp2    134535353535
7       wyp3    132453535353
8       wyp4    154243434355
1       wyp     13188888888888
2       test    13888888888888
3       zs      899314121
Time taken: 0.089 seconds, Fetched: 7 row(s)
```

&emsp;&emsp;数据就插入到test4表中去了，CTAS操作是原子的，因此如果select查询由于某种原因而失败，新表是不会创建的！


<br>

### 2.2 Hive数据导出

&emsp;&emsp;Hive中的几种不同的数据导出方式。可以根据导出的地方不一样，将这些方式分为三种：

&emsp;&emsp;导出到本地文件系统；

&emsp;&emsp;导出到HDFS中；

&emsp;&emsp;导出到Hive的另一个表中。

#### 2.2.1 导入到本地文件系统

```bash
hive> insert overwrite local directory '/home/wyp/wyp'
    > select * from wyp;
```

&emsp;&emsp;这条HQL的执行需要启用Mapreduce完成，运行完这条语句之后，将会在本地文件系统的/home/wyp/wyp目录下生成文件，这个文件是Reduce产生的结果（这里生成的文件名是000000_0），我们可以看看这个文件的内容：

```
[wyp@master ~/wyp]$ vim 000000_0
5^Awyp1^A23^A131212121212
6^Awyp2^A24^A134535353535
7^Awyp3^A25^A132453535353
8^Awyp4^A26^A154243434355
1^Awyp^A25^A13188888888888
2^Atest^A30^A13888888888888
3^Azs^A34^A899314121
```

&emsp;&emsp;可以看出，这就是wyp表中的所有数据。数据中的列与列之间的分隔符是 ^A (ascii码是 \00001 )。

&emsp;&emsp;也可以写成：

```bash
hive> insert overwrite local directory '/home/iteblog/local'
    > row format delimited
    > fields terminated by '\t'
    > select * from wyp;
 
[wyp@master ~/local]$ vim 000000_0
5       wyp1    23      131212121212
6       wyp2    24      134535353535
7       wyp3    25      132453535353
8       wyp4    26      154243434355
1       wyp     25      13188888888888
2       test    30      13888888888888
3       zs      34      899314121
```

#### 2.2.2 导出到HDFS中

&emsp;&emsp;和导入数据到本地文件系统一样的简单，可以用下面的语句实现：

```bash
hive> insert overwrite directory '/home/wyp/hdfs'
    > select * from wyp;
```

&emsp;&emsp;将会在HDFS的 /home/wyp/hdfs 目录下保存导出来的数据。注意，和导出文件到本地文件系统的HQL少一个local，数据的存放路径就不一样了。


#### 2.2.3 导出到Hive的另一个表中

&emsp;&emsp;其实这个在Hive几种数据导入方式中就用到了，这也是Hive的数据导入方式，如下操作：

```bash
hive> insert into table test
    > partition (age='25')
    > select id, name, tel
    > from wyp;
#####################################################################
           这里输出了一堆Mapreduce任务信息，这里省略
#####################################################################
Total MapReduce CPU Time Spent: 1 seconds 310 msec
OK
Time taken: 19.125 seconds
 
hive> select * from test;
OK
5       wyp1    131212121212    25
6       wyp2    134535353535    25
7       wyp3    132453535353    25
8       wyp4    154243434355    25
1       wyp     13188888888888  25
2       test    13888888888888  25
3       zs      899314121       25
Time taken: 0.126 seconds, Fetched: 7 row(s)
```

&emsp;&emsp;其实，我们还可以用hive的 -e 和 -f 参数来导出数据。其中-e 表示后面直接接带双引号的sql语句；而-f是接一个文件，文件的内容为一个sql语句，如下：

```bash
[wyp@master ~/local]$  hive -e "select * from wyp" >> local/wyp.txt
[wyp@master ~/local]$  cat wyp.txt
5       wyp1    23      131212121212
6       wyp2    24      134535353535
7       wyp3    25      132453535353
8       wyp4    26      154243434355
1       wyp     25      13188888888888
2       test    30      13888888888888
3       zs      34      899314121
```

&emsp;&emsp;得到的结果也是用 \t 分割的。也可以用-f参数实现：

```bash
[wyp@master ~/local]$ cat wyp.sql
select * from wyp
[wyp@master ~/local]$ hive -f wyp.sql >> local/wyp2.txt
```

&emsp;&emsp;上述语句得到的结果也是 \t 分割的。

<br>
<br>
<br>
<br>

## Reference:
1.[Hive的几种数据导入方式](https://www.iteblog.com/archives/949.html)

2.[Hive几种数据导出方式](https://www.iteblog.com/archives/955.html)

