# Hadoop学习笔记

<br>
<br>

## 1 Hadoop体系结构

HDFS和MapReduce是Hadoop的两大核心。HDFS支持分布式存储。MapReduce是一种并行编程模式，实现分布式计算和和任务处理。

## 2 MapReduce计算模型

**MapReduce的数据流和控制流：**

Hadoop中负责控制及调度MapReduce的Job是JobTracker，负责运行MapReduce的Job是TaskTracker。MapReduce是在运行时是分成Map Task和Reduce Task来处理的，而不是完整的Job。简答的控制流大概是：JobTracker 调度任务给TaskTracker，TaskTracker执行任务时，会返回进度报告。JobTracker则会记录进度的进行状况，如果某个TaskTracker上的任务执行失败，那么JobTracker会把这个任务分配给另一台TaskTracker，直到任务执行完成。

需注意：

1）MapReduce在执行过程中往往不止一个Reduce Task，Reduce Task的数量是可以程序指定的。当存在多个Reduce Task时，每个Reduce会搜集一个或多个key值。需要注意的是，当出现多个Reduce Task时，每个Reduce Task都会生成一个输出文件。

2）另外，没有Reduce任务的时候，系统会直接将Map的输出结果作为最终结果，同时Map Task的数量可以看做是Reduce Task的数量，即有多少个Map Task就有多少个输出文件。


**MapReduce任务的优化：**

MapReduce模型的优化主要集中在两个方面，一是计算性能方面的优化，二是I/O操作方面的优化。

