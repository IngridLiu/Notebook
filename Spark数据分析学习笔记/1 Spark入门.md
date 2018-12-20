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

### 1.1 Spark核心概念介绍

从上层来看，每个Spark应用都由一个驱动器程序（driver program）来发起集群上的各种并行操作。驱动器程序通过一个SparkContext对象来访问Spark。这个对象代表对计算集群的一个连接。shell 启动时已经自动创建了一个SparkContext 对象，是一个叫作sc 的变量。驱动器程序一般要管理多个执行器节点。

```bash
scala> val lines = sc.textFile("README.md") // 创建一个叫lines的RDD
lines: spark.RDD[String] = MappedRDD[...]

scala> val pythonLines = lines.filter(line => line.contains("Python"))
pythonLines: spark.RDD[String] = FilteredRDD[...]

scala> pythonLines.first()
res0: String = ## Interactive Python Shell
```

在scala中初始化Spark

```scala
import org.apache.spark.SparkConf
import org.apache.spark.SparkContext
import org.apache.spark.SparkContest._

val conf = new SparkConf().setMaster("local").setAppName("My App")
val sc = new SparkContext(conf)
```

以上例子展示了创建SparkContext 的最基本的方法，你只需传递两个参数：

• 集群URL：告诉Spark如何连接到集群上。在这几个例子中我们使用的是local，这个特殊值可以让Spark 运行在单机单线程上而无需连接到集群。

• 应用名：在例子中我们使用的是My App。当连接到一个集群时，这个值可以帮助你在集群管理器的用户界面中找到你的应用。

最后，关闭Spark可以调用SparkContext的stop()方法，或者直接退出应用（比如通过System.exit(0) 或者sys.exit()）。

### 1.2 Spark 运行模式

- local模式：

- standalone模式：

- yarn模式：spark用yarn做资源管理和分配。

- mesos模式：spark用mesos替代yarn做资源管理和分配。

Spark shell 可用来与分布式存储在许多机器的内存或者硬盘上的数据进行交互，并且处理过程的分发由Spark 自动控制完成。

<br>

小例子：Scala 版本的单词数统计应用

```scala
// 创建一个scala版本的SparkContext
val conf = new SparkConf().setAppName("wordCount")
val sc = new SparkContext(conf)
// 读取我们的输入数据
val input = sc.textFile(inputFile)
// 把它切分呈一个个单词
val words = input.flatMap(line => line.split(" "))
val counts = words.map(word => (word, 1)).reduceByKey{case (x, y) => x + y}
// 将统计出来的单词总数存入一个文本文件，引发求值
counts.saveAsTextFile(outputFile)
```

<br>

## 2. 核心概念RDD(Resilient Distributed Datasets,RDD)

&emsp;&emsp;RDD是弹性分布式数据库(Resilient Distributed Datasets,RDD)。Spark中的RDD就是一个不可变的分布式对象集合。每个RDD都被分为多个分区，这些分区运行在集群中的不同节点上。用户可以使用两种方法创建RDD：读取一个外部数据集，或在驱动程序里分发驱动器程序中的对象集合（比如list和set）。创建出来后，RDD支持两种类型的操作：转化操作（transformation）和行动操作（action）。转化操作会由一个RDD生成一个新的RDD。行动操作会对RDD计算出一个结果，并把结果返回到驱动器程序中，或把结果存储到外部存储系统（如HDFS）中。转化操作和行动操作的区别在于Spark 计算RDD 的方式不同。虽然你可以在任何时候定义新的RDD，但Spark 只会惰性计算这些RDD。它们只有第一次在一个行动操作中用到时，才会真正计算。默认情况下，Spark 的RDD 会在你每次对它们进行行动操作时重新计算。如果想在多个行动操作中重用同一个RDD，可以使用RDD.persist() 让Spark 把这个RDD 缓存下来。在实际操作中，你会经常用persist() 来把数据的一部分读取到内存中，并反复查询这部分数据。如下：

```scala
pythonLines.persist

pythonLines.count()
pythonLines.firts()
```

总的来说，每个Spark 程序或shell 会话都按如下方式工作。

(1) 从外部数据创建出输入RDD。

(2) 使用诸如filter() 这样的转化操作对RDD 进行转化，以定义新的RDD。

(3) 告诉Spark 对需要被重用的中间结果RDD 执行persist() 操作。

(4) 使用行动操作（例如count() 和first() 等）来触发一次并行计算，Spark会对计算进行优化后再执行。






## Reference:

1. [《Spark快速大数据分析》]()