# Spark入门


<br>
<br>

&emsp;&emsp;Spark 是一个用来实现快速而通用的集群计算的平台。Spark是内存计算引擎,支持scala开发，支持java scala python开发接口。

## 1. Spark 组件介绍

Spark的各个组件如图所示：

![图1:Spark软件栈](https://upload-images.jianshu.io/upload_images/10947003-7d265dd5ff127f8a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/600)

Spark Core 实现了Spark 的基本功能，包含任务调度、内存管理、错误恢复、与存储系统交互等模块。Spark Core 中还包含了对弹性分布式数据集（resilient distributed dataset，简称RDD）的API 定义。RDD 表示分布在多个计算节点上可以并行操作的元素集合，是Spark 主要的编程抽象。Spark Core 提供了创建和操作这些集合的多个API。

Spark SQL 是Spark 用来操作结构化数据的程序包。通过Spark SQL，我们可以使用SQL或者Apache Hive 版本的SQL 方言（HQL）来查询数据。Spark SQL 支持多种数据源，比如Hive 表、Parquet 以及JSON 等。除了为Spark 提供了一个SQL 接口，Spark SQL 还支持开发者将SQL 和传统的RDD 编程的数据操作方式相结合.

Spark Streaming 是Spark 提供的对实时数据进行流式计算的组件。

Spark 中还包含一个提供常见的机器学习（ML）功能的程序库，叫作MLlib。MLlib 提供了很多种机器学习算法，包括分类、回归、聚类、协同过滤等，还提供了模型评估、数据导入等额外的支持功能。

GraphX 是用来操作图（比如社交网络的朋友关系图）的程序库，可以进行并行的图计算。

## 1.Spark 运行模式

- local模式：

- standalone模式：

- yarn模式：spark用yarn做资源管理和分配。

- mesos模式：spark用mesos替代yarn做资源管理和分配。

Spark shell 可用来与分布式存储在许多机器的内存或者硬盘上的数据进行交互，并且处理过程的分发由Spark 自动控制完成。

## 2. 核心概念RDD(Resilient Distributed Datasets,RDD)

&emsp;&emsp;RDD是弹性分布式数据库(Resilient Distributed Datasets,RDD)，






## Reference:

1. [《Spark快速大数据分析》]()