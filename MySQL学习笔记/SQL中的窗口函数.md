# SQL中的窗口函数

<br>
<br>
<br>
<br>

## 1. 窗口函数介绍

&emsp;&emsp;窗口函数是 SQL 中一类特别的函数。和聚合函数相似，窗口函数的输入也是多行记录。不 同的是，聚合函数的作用于由 GROUP BY 子句聚合的组，而窗口函数则作用于一个窗口， 这里，窗口是由一个 OVER 子句 定义的多行记录。聚合函数对其所作用的每一组记录输 出一条结果，而窗口函数对其所作用的窗口中的每一行记录输出一条结果。一些聚合函 数，如 sum, max, min, avg,count 等也可以当作窗口函数使用。

&emsp;&emsp;与聚集函数一样，窗口函数也针对定义的行集（组）执行聚集，但它不像聚集函数那样每组之返回一个值，窗口函数可以为每组返回多个值。实际上，DB2中称这种函数为联机分析处理OLAP函数，而Oracle把它们称为解析函数，但ISO SQL标准把它们称为窗口函数。窗口函数一般在OLAP分析、制作报表过程中会使用到。

&emsp;&emsp;窗口函数多和OVER、PARTITION BY，ORDER BY，WINDOWING配合使用。

&emsp;&emsp;窗口函数语法形式如下：

```sql
Function(arg1, ..., argn) OVER([PARTITION BY <...>] [ORDER BY <...>] [window_clause])
```

## 2. 窗口函数中的子句

**窗口函数：**

|函数|说明|
|:----|:----|
|FIRST_VALUE|取出分组内排序后，截止到当前行，第一个值|
|LAST_VALUE|取出分组内排序后，截止到当前行，最后一个值|
|LEAD(col, n, DEFAULT)|用于统计窗口内往下第n行的值。第一个参数为列名，第二个参数为往下第n行（可选，默认为1），第三个参数为默认值（当往下第n行为NULL时，取默认值）|
|LAG(col, n, DEFAULT)|与lead相反，用于统计窗口内网上第n个值。第一个参数为列名，第二个参数往上为第n行(可选，默认为1)|

**分析函数：**

|函数|说明|
|:----|:----|
|ROW_NUMBER()|从1开始，按照顺序，生成分组内记录的序列，比如，按照pv降序排列，生成分组内每天的pv名次，ROW_NUMBER()的应用场景非常多，再比如，获取分组内排序第一的记录，获取一个session中的第一条refer等|
|RANK()|生成数据项在分组中的排名，排名相等会在名次中留下空位|
|DENSE_RANK()|生成数据项在分组中的排名，排名相等不会在名次中留下空位|
|CUME_DIST()|小于等于当前值的行数除以分组内总行数。比如，统计小于等于当前薪水的人数所占总人数的比例|
|PERCENT_RANK()|（分组内当前行的RANK值-1）/（分组内总行数）|

**OVER从句：**

1. 使用标准的聚合函数COUNT、SUM、MIN、MAX、AVG。

2. 使用PARTITION BY语句，使用一个或者多个原始数据类型的列。

3. 使用PARTITION BY与ORDER BY语句，使用一个或者多个数据类型的分区或者排序列。

4. 使用窗口规范，窗口规范支持一下格式：

```sql
(ROW | RANGE) BETWEEN (UNBOUNDED | [num]) PRECEDING AND ([num] PRECEDING | CURRENT ROW | (UNBOUNDED | [num]) FOLLOWING)
(ROW | RANGE) BETWEEN CURRENT ROW AND (CURRENT ROW | (UNBOUNDED | [num]) FOLLOWING)
(ROW | RANGE) BETWEEN [num] PRECEDING AND (UNBOUNDED | [num]) FOLLOWING
```

&emsp;&emsp;当ORDER BY后面缺少窗口从句条件，窗口规范默认是:

```sql
RANGE BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
```

&emsp;&emsp;当ORDER BY和窗口从句都缺失，窗口规范默认是：

```sql
ROW BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING
```

&emsp;&emsp;窗口规范示例：

```sql
-- 默认从起点到当前所有重复行
sum(sales) over(partition by user_type order by sales asc) as sales_1,
-- 从起点到当前所有重复行与sales_1结果相同
sum(sales) over(partition by user_type order by sales asc range between unbounded preceding and current row) as sales_2,
-- 从起点到当前行，结果与sale_1结果不同
sum(sales) over(partition by user_type order by sales asc rows between unbounded preceding and current row) as sales_3,
-- 当前行加上往前3行
sum(sales) over(partition by user_type order by sales asc rows between 3 preceding and current row) as sales_4,
-- 当前范围往上加3行
sum(sales) over(partition by user_type order by sales asc range between 3 preceding and current row) as sales_5,
-- 当前行+往前3行+往后1行
sum(sales) over(partition by user_type order by sales asc rows between 3 preceding and 1 following) as sales_6,
--
sum(sales) over(partition by user_type order by sales asc range between 3 preceding and 1 following) as sales_7,
-- 当前行+之后所有行
sum(sales) over(partition by user_type order by sales asc rows between current row and unbounded following) as sales_8,
--
sum(sales) over(partition by user_type order by sales asc range between current row and unbounded following) as sales_9,
-- 分组内所有行
sum(sales) over(partition by user_type) as sales_10
```

 <br>
 
 ## 2. 窗口函数做筛选
 
&emsp;&emsp;窗口函数只允许出现在查询的SELECT列表和ORDER BY子句中。它们不允许出现在其他地方，例如GROUP BY、HAVING和WHERE子句中。这是因为窗口函数的执行逻辑是在处理完这些子句之后。另外，窗口函数在非窗口聚集函数之后执行。这意味着可以在窗口函数的参数中包括一个聚集函数，但反过来不行。

&emsp;&emsp;如果需要在窗口计算执行后进行过滤或者分组，我们可以使用子查询。例如：

```sql
SELECT depname, empno, salary, enroll_date
FROM
  (SELECT depname, empno, salary, enroll_date,
          rank() OVER (PARTITION BY depname ORDER BY salary DESC, empno) AS pos
     FROM empsalary
  ) AS ss
WHERE pos < 3;
```
 
&emsp;&emsp;上述查询仅仅显示了内层查询中rank低于3的结果。

&emsp;&emsp;当一个查询涉及到多个窗口函数时，可以将每一个分别写在一个独立的OVER子句中。但如果多个函数要求同一个窗口行为时，这种做法是冗余的而且容易出错的。替代方案是，每一个窗口行为可以被放在一个命名的WINDOW子句中，然后在OVER中引用它。例如：

```sql
SELECT sum(salary) OVER w, avg(salary) OVER w
FROM empsalary
WINDOW w AS (PARTITION BY depname ORDER BY salary DESC);
```




<br>
<br>

## Reference:

1. [如何理解窗口函数](https://blog.csdn.net/sinat_29581293/article/details/77479330)

2. [Hive分析函数和窗口函数](https://www.jianshu.com/p/acc8b158daef)

3. [窗口函数](http://www.postgres.cn/docs/10/tutorial-window.html)