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

```bash
hive> load data local inpath 'wyp.txt' into table wyp; -- 从本地文件系统中导入数据到Hive表

hive> load data inpath '/home/wyp/add.txt' into table wyp; -- HDFS上导入数据到Hive表

hive> insert into table test
    > partition (age='25')
    > select id, name, tel
    > from wyp; -- 从别的表中查询出相应的数据并导入到Hive表中
    
hive> create table test4
    > as
    > select id, name, tel
    > from wyp; -- 在创建表的时候通过从别的表中查询出相应的记录并插入到所创建的表中

```

> 和我们熟悉的关系型数据库不一样，Hive现在还不支持在insert语句里面直接给出一组记录的文字形式，也就是说，Hive并不支持INSERT INTO .... VALUES形式的语句。

### 2.2 Hive数据导出


```bash
hive> insert overwrite local directory '/home/iteblog/local'
    > row format delimited
    > fields terminated by '\t'
    > select * from wyp;    -- 导出到本地文件系统
    
hive> insert overwrite directory '/home/wyp/hdfs'
    > select * from wyp;    -- 导出到hdfs
   
hive> insert into table test
    > partition (age='25')
    > select id, name, tel
    > from wyp;     -- 导出到Hive的另一个表中

```



<br>
<br>
<br>
<br>

## Reference:
1.[Hive的几种数据导入方式](https://www.iteblog.com/archives/949.html)

2.[Hive几种数据导出方式](https://www.iteblog.com/archives/955.html)

