# SQL聚合函数

<br>
<br>
<br>
<br>

## 1 SQL中的聚合函数

## 2.GROUP BY语句

&emsp;&emsp;GROUP BY语句用来与聚合函数(aggregate functions such as COUNT, SUM, AVG, MIN, or MAX.)联合使用来得到一个或多个列的结果集。

&emsp;&emsp;语法如下：

```sql
SELECT column1, column2, ... column_n, aggregate_function (expression)            
FROM tables            
WHERE predicates            
GROUP BY column1, column2, ... column_n;
```

&emsp;&emsp;示例：

```sql
-- 查询学生选择课程数
SELECT id, COUNT(course) as numcourse
FROM student
GROUP BY id
```

&emsp;&emsp;注意

&emsp;&emsp;因为聚合函数通过作用于一组数据而只返回一个单个值，因此，在SELECT语句中出现的元素要么为一个聚合函数的输入值，要么为GROUP BY语句的参数，否则会出错。

<br>

## 3. HAVING语句

&emsp;&emsp;HAVING语句通常与GROUP BY语句联合使用，用来过滤由GROUP BY语句返回的记录集。

&emsp;&emsp;HAVING语句的存在弥补了WHERE关键字不能与聚合函数联合使用的不足。

&emsp;&emsp;语法：

```sql
SELECT column1, column2, ... column_n, aggregate_function (expression)
FROM tables
WHERE predicates
GROUP BY column1, column2, ... column_n
HAVING condition1 ... condition_n;
```

&emsp;&emsp;示例:

```sql
-- 查询平均分高于80分的学生记录可以这样写：
SELECT id, COUNT(course) as numcourse, AVG(score) as avgscore
FROM student
GROUP BY id
HAVING AVG(score)>=80;
```

<br>
<br>
<br>
<br>

## Reference：
1.[SQL中GROUP BY语句与HAVING语句的使用](https://www.cnblogs.com/8335IT/p/5850531.html)