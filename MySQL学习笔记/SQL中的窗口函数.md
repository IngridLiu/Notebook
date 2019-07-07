# SQL中的窗口函数

<br>
<br>
<br>
<br>

## 1. 窗口调用函数介绍

&emsp;&emsp;窗口函数是 SQL 中一类特别的函数。和聚合函数相似，窗口函数的输入也是多行记录。不 同的是，聚合函数的作用于由 GROUP BY 子句聚合的组，而窗口函数则作用于一个窗口， 这里，窗口是由一个 OVER 子句 定义的多行记录。聚合函数对其所作用的每一组记录输 出一条结果，而窗口函数对其所作用的窗口中的每一行记录输出一条结果。一些聚合函 数，如 sum, max, min, avg,count 等也可以当作窗口函数使用。

&emsp;&emsp;与聚集函数一样，窗口函数也针对定义的行集（组）执行聚集，但它不像聚集函数那样每组之返回一个值，窗口函数可以为每组返回多个值。实际上，DB2中称这种函数为联机分析处理OLAP函数，而Oracle把它们称为解析函数，但ISO SQL标准把它们称为窗口函数。窗口函数一般在OLAP分析、制作报表过程中会使用到。

&emsp;&emsp;窗口函数多和OVER、PARTITION BY，ORDER BY，WINDOWING配合使用。

&emsp;&emsp;窗口函数语法形式如下：

```sql
function_name ([expression [, expression ... ]]) OVER ( window_definition )
function_name ([expression [, expression ... ]]) OVER window_name
function_name ( * ) OVER ( window_definition )
function_name ( * ) OVER window_name
```



## 2. function_name窗口函数

**窗口函数：**

|函数|说明|
|:----|:----|
|FIRST_VALUE|取出分组内排序后，截止到当前行，第一个值|
|LAST_VALUE|取出分组内排序后，截止到当前行，最后一个值|
|LEAD(col, n, DEFAULT)|用于统计窗口内往下第n行的值。第一个参数为列名，第二个参数为往下第n行（可选，默认为1），第三个参数为默认值（当往下第n行为NULL时，取默认值）|
|LAG(col, n, DEFAULT)|与lead相反，用于统计窗口内往上第n个值。第一个参数为列名，第二个参数往上为第n行(可选，默认为1)|

**分析函数：**

|函数|说明|
|:----|:----|
|ROW_NUMBER()|从1开始，按照顺序，生成分组内记录的序列，比如，按照pv降序排列，生成分组内每天的pv名次，ROW_NUMBER()的应用场景非常多，再比如，获取分组内排序第一的记录，获取一个session中的第一条refer等|
|RANK()|生成数据项在分组中的排名，排名相等会在名次中留下空位|
|DENSE_RANK()|生成数据项在分组中的排名，排名相等不会在名次中留下空位|
|CUME_DIST()|小于等于当前值的行数除以分组内总行数。比如，统计小于等于当前薪水的人数所占总人数的比例|
|PERCENT_RANK()|（分组内当前行的RANK值-1）/（分组内总行数）|

## 3. window_definition OVER从句

&emsp;&emsp;这里的window_definition具有如下语法：

```sql
[ existing_window_name ]
[ PARTITION BY expression [, ...] ]
[ ORDER BY expression [ ASC | DESC | USING operator ] [ NULLS { FIRST | LAST } ] [, ...] ]
[ frame_clause ]
```

### 3.1 existing_window_name子句

&emsp;&emsp;window_name引用的是查询语句中WINDOW 子句定义的命名窗口规范。命名窗口规范通常只是用OVER window_name 来引用，但它也可以在括号里写一个窗口名，并且可以有选择的使用排序和/或框架(frame）子句 （如果应用这些子句的话，那么被引用的窗口必须不能有这些子句）。 后者语法遵循相同的规则（修改WINDOW子句中已有的窗口名）。

### 3.2 PARTITION BY 子句

&emsp;&emsp;PARTITION BY选项将查询的行分为一组进入partitions， 这些行在窗口函数中单独处理。PARTITION BY和查询级别GROUP BY 子句做相似的工作，除了它的表达式只能作为表达式不能作为输出列的名字或数。 没有PARTITION BY，所有由查询产生的行被视为一个单独的分区。

### 3.3 ORDER BY 子句

&emsp;&emsp;ORDER BY 选项决定分区中的行被窗口函数处理的顺序。它和查询级别ORDER BY子句做相似的工作， 但是同样的它不能作为输出列的名字或数。没有ORDER BY，行以一个不被预知的顺序处理。

### 3.4 frame_clause 子句

&emsp;&emsp;对这些窗口函数（在这个框架而不是整个分区上的）， frame_clause指定构成window frame的行， 他们是当前分区的一个子集。框架可以用RANGE 或 ROWS模式声明；不管哪种情况， 它的变化范围是从frame_start到frame_end。如果省略了frame_end 默认为CURRENT ROW。

&emsp;&emsp;选项frame_clause可以是：

```sql
[ RANGE | ROWS ] frame_start
[ RANGE | ROWS ] BETWEEN frame_start AND frame_end
```

&emsp;&emsp;frame_start 和 frame_end可以是：

```sql
UNBOUNDED PRECEDING
value PRECEDING
CURRENT ROW
UNBOUNDED FOLLOWING
value FOLLOWING
```

&emsp;&emsp;一个frame_start的UNBOUNDED PRECEDING意味着框架从分区中的第一行开始， 相似的，一个frame_end的UNBOUNDED FOLLOWING意味着框架从分区中的最后一行结束。

&emsp;&emsp;在RANGE模式中，frame_start的CURRENT ROW 意味着框架从当前行的第一个peer行开始（ORDER BY 认为等于当前行的行），而frame_end的CURRENT ROW 意味着框架从最后一个同等的行结束。在ROWS模式中， CURRENT ROW 简单的意味着当前行。

&emsp;&emsp;value PRECEDING和value FOLLOWING 当前只允许ROWS模式。这也就意味着，框架从当前行之前或之后指定的行数启动或结束。 value必须是整型表达式，而不能包含变量，聚合函数，或者窗口函数。 该值不能为空或负，但可以是零，表示只选择当前行本身。

&emsp;&emsp;默认的框架选项是RANGE UNBOUNDED PRECEDING，该选项与 RANGE BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW相同。有ORDER BY， 它设置框架从分区的开始一直到与当前行相同的最后一行。没有ORDER BY， 那么就是当前分区的所有行都包含在框架中，因为所有行都会成为当前行的相同行。

&emsp;&emsp;限制条件是frame_start不能为UNBOUNDED FOLLOWING， frame_end不能为UNBOUNDED PRECEDING，并且frame_end 选项不能在上面的列表中出现的比frame_start选项早—例如 RANGE BETWEEN CURRENT ROW AND value PRECEDING是不被允许的。

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
 
 ## 4. 窗口函数做筛选
 
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

4. [值表达式](http://www.postgres.cn/docs/9.3/sql-expressions.html#SYNTAX-WINDOW-FUNCTIONS))