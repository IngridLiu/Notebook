# 2 MySQL数据库操作

<br>
<br>
<br>
<br>

## 3.1 MySQL操作数据库

<br>

## 3.2 MySQL操作数据表

### 3.2.1 MySQL创建数据库表

&emsp;&emsp;创建MySQL数据表的SQL通用语法：

```
CREATE TABLE table_name (column_name column_type);
```

&emsp;&emsp;以下例子中我们将在 RUNOOB 数据库中创建数据表runoob_tbl：

```
CREATE TABLE IF NOT EXISTS `runoob_tbl`(
   `runoob_id` INT UNSIGNED AUTO_INCREMENT,
   `runoob_title` VARCHAR(100) NOT NULL,
   `runoob_author` VARCHAR(40) NOT NULL,
   `submission_date` DATE,
   PRIMARY KEY ( `runoob_id` )
)ENGINE=InnoDB DEFAULT CHARSET=utf8;
```
<br>

### 3.2.2 MySQL删除数据库表

&emsp;&emsp;以下为删除MySQL数据表的通用语法：

```
DROP TABLE table_name ;
```

&emsp;&emsp;以下实例删除了数据表runoob_tbl:

```
DROP TABLE runoob_tbl
```

<br>

## 3.3 数据库表数据操作

### 3.3.1 数据库表查询

&emsp;&emsp;以下为在MySQL数据库中查询数据通用的 SELECT 语法：

```
SELECT column_name,column_name
FROM table_name
[WHERE Clause]
[LIMIT N][ OFFSET M]
```

&emsp;&emsp;查询语句中你可以使用一个或者多个表，表之间使用逗号(,)分割，并使用WHERE语句来设定查询条件。

&emsp;&emsp;SELECT 命令可以读取一条或者多条记录。

&emsp;&emsp;你可以使用星号（*）来代替其他字段，SELECT语句会返回表的所有字段数据

&emsp;&emsp;你可以使用 WHERE 语句来包含任何条件。

&emsp;&emsp;你可以使用 LIMIT 属性来设定返回的记录数。

&emsp;&emsp;你可以通过OFFSET指定SELECT语句开始查询的数据偏移量。默认情况下偏移量为0。

&emsp;&emsp;以下实例将返回数据表 runoob_tbl 的所有记录:

```
select * from runoob_tbl;
```

### 3.3.1 数据库表插入数据

&emsp;&emsp;以下为向MySQL数据表插入数据通用的 INSERT INTO SQL语法：

```
INSERT INTO table_name ( field1, field2,...fieldN )
                       VALUES
                       ( value1, value2,...valueN );
```
&emsp;&emsp;以下实例中我们将向 runoob_tbl 表插入数据:

```
INSERT INTO runoob_tbl (runoob_title, runoob_author, submission_date) VALUES ("学习 PHP", "菜鸟教程", NOW());
```

### 3.3.2 数据库表更新数据

&emsp;&emsp;以下是 UPDATE 命令修改 MySQL 数据表数据的通用 SQL 语法：

```
UPDATE table_name SET field1=new-value1, field2=new-value2 [WHERE Clause]
```

&emsp;&emsp;你可以同时更新一个或多个字段。

&emsp;&emsp;你可以在 WHERE 子句中指定任何条件。

&emsp;&emsp;你可以在一个单独表中同时更新数据。

&emsp;&emsp;当你需要更新数据表中指定行的数据时 WHERE 子句是非常有用的。

&emsp;&emsp;以下实例将更新数据表中 runoob_id 为 3 的 runoob_title 字段值：

```
UPDATE runoob_tbl SET runoob_title='学习 C++' WHERE runoob_id=3;
```

### 3.3.3 数据库表删除数据

&emsp;&emsp;以下是 SQL DELETE 语句从 MySQL 数据表中删除数据的通用语法：

```
DELETE FROM table_name [WHERE Clause]
```

&emsp;&emsp;实例：

```
DELETE FROM runoob_tbl WHERE runoob_id=3;
```

<br>
<br>
<br>
<br>





Reference:
1. [MySQL 创建数据表](http://www.runoob.com/mysql/mysql-create-tables.html)
2. [MySQL 删除数据表](http://www.runoob.com/mysql/mysql-drop-tables.html)
3. [MySQL 查询数据](http://www.runoob.com/mysql/mysql-select-query.html)
4. [MySQL 插入数据](http://www.runoob.com/mysql/mysql-insert-query.html)
5. [MySQL 更新数据](http://www.runoob.com/mysql/mysql-update-query.html)
6. [MySQL DELETE 语句](http://www.runoob.com/mysql/mysql-delete-query.html)
