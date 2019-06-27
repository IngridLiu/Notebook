# SQL表连接(INNER JOIN, LEFT JOIN, RIGHT JOIN, FULL OUTER JOIN, UNION, UNION ALL)

<br>
<br>
<br>
<br>

&emsp;&emsp;假设我们有两张表。Table A 是左边的表。Table B 是右边的表。其各有四条记录，其中有两条记录name是相同的，如下所示：让我们看看不同JOIN的不同



##1. INNER JOIN

&emsp;&emsp;SELECT * FROM TableA INNER JOIN TableB ON TableA.name = TableB.name

![](http://justcode.ikeepstudying.com/wp-content/uploads/2016/08/20133181224183.png)

<br>

## 2. FULL [OUTER] JOIN

(1)

&emsp;&emsp;SELECT * FROM TableA FULL OUTER JOIN TableB ON TableA.name = TableB.name

![](http://justcode.ikeepstudying.com/wp-content/uploads/2016/08/2013318122434269.png)

(2) SELECT * FROM TableA FULL OUTER JOIN TableB ON TableA.name = TableB.name
WHERE TableA.id IS null OR TableB.id IS null

![](http://justcode.ikeepstudying.com/wp-content/uploads/2016/08/2013318122921410.png)

<br>

## 3. LEFT [OUTER] JOIN

(1) SELECT * FROM TableA LEFT OUTER JOIN TableB ON TableA.name = TableB.name

![](http://justcode.ikeepstudying.com/wp-content/uploads/2016/08/2013318122936847.png)

(2) SELECT * FROM TableA LEFT OUTER JOIN TableB ON TableA.name = TableB.name WHERE TableB.id IS null

![](http://justcode.ikeepstudying.com/wp-content/uploads/2016/08/201331812295082.png)

<br>

## 4. RIGHT [OUTER] JOIN

&emsp;&emsp;RIGHT OUTERJOIN 是后面的表为基础，与LEFT OUTER JOIN用法类似。这里不介绍了。

<br>

## 5.UNION 与 UNION ALL

&emsp;&emsp;UNION 操作符用于合并两个或多个 SELECT 语句的结果集。 

&emsp;&emsp;请注意，UNION 内部的 SELECT 语句必须拥有相同数量的列。列也必须拥有相似的数据类型。同时，每条 SELECT 语句中的列的顺序必须相同。UNION 只选取记录，而UNION ALL会列出所有记录。

(1)SELECT name FROM TableA UNION SELECT name FROM TableB

![](https://images0.cnblogs.com/blog/407365/201405/231634089816605.png)

&emsp;&emsp;选取不同值

(2)SELECT name FROM TableA UNION ALL SELECT name FROM TableB

![](https://images0.cnblogs.com/blog/407365/201405/231634095596262.png)

&emsp;&emsp;全部列出来

(3)注意:

&emsp;&emsp;SELECT * FROM TableA UNION SELECT * FROM TableB

![](https://images0.cnblogs.com/blog/407365/201405/231634111682503.png)

&emsp;&emsp;由于 id 1 Pirate   与 id 2 Pirate 并不相同，不合并

&emsp;&emsp;还需要注册的是我们还有一个是“交差集” cross join, 这种Join没有办法用文式图表示，因为其就是把表A和表B的数据进行一个N*M的组合，即笛卡尔积。表达式如下：SELECT * FROM TableA CROSS JOIN TableB

&emsp;&emsp;这个笛卡尔乘积会产生 4 x 4 = 16 条记录，一般来说，我们很少用到这个语法。但是我们得小心，如果不是使用嵌套的select语句，一般系统都会产生笛卡尔乘积然再做过滤。这是对于性能来说是非常危险的，尤其是表很大的时候。

<br>

## 6. SUMMARY

![](https://images0.cnblogs.com/i/407365/201405/241947220904425.jpg)