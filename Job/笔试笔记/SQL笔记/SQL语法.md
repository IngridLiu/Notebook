# SQL语法

<br>
<br>

## 5. SQL的视图

视图可以用来定义新的视图；

视图一经定义就无法修改；

## 1. SQL语句的执行顺序

语法顺序：SELECT ... FROM ... WHERE ... GROUP BY ... HAVING ... ORDER BY ... LIMIT ... 

执行顺序：FROM ... WHERE ... GROUP BY ... HAVING ... SELECT ... ORDER BY ... LIMIT 


## 查看SQL模式

mysql中查看SQL模式的命令：

```sql
select @@global.sql_mode
select @@sql_mode
select @@session.sql_mode
```

MySQL数据库中，变量分为 系统变量（以"@@"开头）和用户自定义变量。系统变量分为全局系统变量(global)和会话系统变量(session)。

@@global     仅用于访问全局系统变量的值；

@@session  仅用于访问会话系统变量的值；

@@              先访问会话系统变量的值，若不存在则去访问全局系统变量的值；

sql_mode 为系统变量，既是全局系统变量，又是会话系统变量。

## 通配符

|通配符|含义||
|:----:|:---||
|%|匹配0个或多个字符|
|_|匹配任意一个字符|

示例：
|含义|通配符|
|:---|:----:|
|倒数第三个字母为W，并且至少包含4个字母的字符串|_ % W _ _|