# Hive学习笔记

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

## 2 Hive 数据导入导出

### 2.1 Hive数据导入

&emsp;&emsp;总结Hive的几种常见的数据导入方式，总结为四种：

&emsp;&emsp;从本地文件系统中导入数据到Hive表；

&emsp;&emsp;从HDFS上导入数据到Hive表；

&emsp;&emsp;从别的表中查询出相应的数据并导入到Hive表中；

&emsp;&emsp;在创建表的时候通过从别的表中查询出相应的记录并插入到所创建的表中。

### 2.1.1 从本地文件系统中导入数据到Hive表

### 2.2 Hive数据导出

&emsp;&emsp;Hive中的几种不同的数据导出方式。可以根据导出的地方不一样，将这些方式分为三种：

&emsp;&emsp;导出到本地文件系统；

&emsp;&emsp;导出到HDFS中；

&emsp;&emsp;导出到Hive的另一个表中。

### 2.2.1 导入到本地文件系统

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

&emsp;&emsp也可以写成：

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

### 2.2.2 导出到HDFS中

&emsp;&emsp;和导入数据到本地文件系统一样的简单，可以用下面的语句实现：

```bash
hive> insert overwrite directory '/home/wyp/hdfs'
    > select * from wyp;
```

&emsp;&emsp;将会在HDFS的 /home/wyp/hdfs 目录下保存导出来的数据。注意，和导出文件到本地文件系统的HQL少一个local，数据的存放路径就不一样了。


### 2.2.3 导出到Hive的另一个表中

&emsp;&emsp;其实这个在《Hive几种数据导入方式》文中就用到了，这也是Hive的数据导入方式，如下操作：

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
1.[Hive的几种数据导入方式]()
2.[Hive几种数据导出方式](https://www.iteblog.com/archives/955.html)

