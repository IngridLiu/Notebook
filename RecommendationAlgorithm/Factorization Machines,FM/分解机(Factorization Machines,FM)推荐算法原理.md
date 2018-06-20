# 分解机(Factorization Machines，FM)推荐算法

<br>
<br>
<br>

## 1 分解机(Factorization Machines)推荐算法原理

## 1.1 目录

![](https://upload-images.jianshu.io/upload_images/10947003-adc9ae541282b78d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

<br>

## 1.2 预测任务

![](https://upload-images.jianshu.io/upload_images/10947003-22f117e5d7d0c3f8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/10947003-1df1115bb907e68e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/10947003-a06368022bcb1620.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
<br>

## 1.3 模型方程

![](https://upload-images.jianshu.io/upload_images/10947003-9813f7d7fb01ce60.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/10947003-ec22f80af21c3ffd.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/10947003-6d18001813f56278.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/10947003-0454698051fddaec.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
<br>

## 1.4 回归和分类

![](https://upload-images.jianshu.io/upload_images/10947003-9ff4a7409d960609.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

<br>

## 1.5 学习算法

![](https://upload-images.jianshu.io/upload_images/10947003-98fb977b53f6f286.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/10947003-049cdcb399efc0d8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/10947003-56f0572a56cd7607.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/10947003-41b85ee92151eb89.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

<br>

## 1.6 参考文献

![](https://upload-images.jianshu.io/upload_images/10947003-cae43d95082b6204.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

<br>
<br>

## 2 FM实现工具libfm

### 2.1 安装编译libfm
&emsp;&emsp;libFM has been tested with the GNU compiler collection and GNU make. Both should be available in Linux and MacOS X.
&emsp;&emsp;With the following steps, you can build libFM:
&emsp;&emsp;1. Download libFM source code: http://www.libfm.org/libfm-1.42.src.tar.gz 
&emsp;&emsp;2. Unzip and untar: e.g. tar -xzvf libfm-1.42.src.tar.gz
&emsp;&emsp;3. Enter the directory libfm-1.42.src and compile the tools: make all

- 文件概述

• history.txt︰ 版本历史记录和更改
• readme.pdf︰ libfm的手册
• Makefile︰ 使用make编译的可执行文件
• bin︰ executables（需要使用make来build，见1.1节）的文件夹
— — libFM: libFM 工具
— —  convert︰ 将文字文件转换成二进制格式的工具
— — transpos︰ 转换二进制设计矩阵的一个工具
•  scripts
— — ltriple format to libfm.pl︰ 一个 Perl 脚本将逗号/制表符分隔的数据集 转换成 libFM 格式。
• src︰ 源文件的 libFM 和工具

### 2.2 数据格式

&emsp;&emsp;libFM 支持两种文件格式用于输入数据︰ 文本格式和二进制格式。使用文本格式是更容易的，所以推荐新 libFM 用户使用。

#### 2.2.1 文本格式

&emsp;&emsp;数据格式与SVMlite [3] 和 LIBSVM [1] 相同，每一行都都包含一个训练集（x，y），分别提供给实特征向量x和目标y。行首先规定y的值，然后是x的非零值。
&emsp;&emsp;对于二进制类型，y>0的类型被认为是积极的一类，y<=0被认为是消极的一类。

&emsp;&emsp; 4 0:1.5 3:-7.9
&emsp;&emsp; 2 1:1e-5 3:2
&emsp;&emsp; -1 6:1
&emsp;&emsp; ...

&emsp;&emsp;此文件包含三个case：
&emsp;&emsp;第一列指出的三个case的每个目标︰4是第一个case的，2是第二的，-1是第三个。
&emsp;&emsp;在每个目标之后, 包含非零元素x。如 0:1.5 表示= 1.5 ，3:-7.9 表示= −7.9等等。
&emsp;&emsp;即：左边的值是x 的索引，而右边的是 的值，即 = 值。

&emsp;&emsp;总之，上述例子表示如下设计矩阵X和目标向量y；

![](https://upload-images.jianshu.io/upload_images/10947003-fc34333595b9d13c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/400)

##### 2.2.1.1 转变到推荐文件

&emsp;&emsp;在推荐系统中经常使用像 userid， itemid， rating的这样的文件格式。
&emsp;&emsp;在script文件夹中的perl脚本是用来将这样格式的数据集转换成libFM的格式的。例如，将Movielens 1M里的rating.csv转换成libFM格式，
&emsp;&emsp;使用——
&emsp;&emsp;./triple_format_to_libfm.pl-in ratings.dat -target 2 -delete_column 3 -separator "::"
&emsp;&emsp;输出将写入到一个文件扩展名为.libfm的文件中。例如，写入toratings.dat.libfm中。
&emsp;&emsp;如果一个数据集包含多个文件，如包含训练和测试split，则使用——in后面包含多个文件
&emsp;&emsp;./triple_format_to_libfm.pl -in train.txt,test.txt-target 2 -separator "\t"

&emsp;&emsp;注意：
&emsp;&emsp;如果你为每个文件单独运行一次脚本，则变量（id）将不会匹配了。
&emsp;&emsp;例如，第一个文件中的第n个变量将和第二个文件中的第n个变量不一样了。

#### 2.2.2 二进制文件

&emsp;&emsp;除了标准的文本格式，libFM 支持二进制数据格式。
&emsp;&emsp;该二进制文件的优点：
&emsp;&emsp;（1） 读的速度快
&emsp;&emsp;（2） 如果您的数据不适合到主内存中，二进制数据格式支持将数据缓存在硬盘并在内存中保留只有一小部分 (使用 — — 高速缓存的大小在 libFM)，
&emsp;&emsp;（3）如果你使用的 ALS 和 mcmc 方法，你可以预先计算换位的设计矩阵，这可以节省读取数据集时的时间。
&emsp;&emsp;使用bin文件夹下的【如下】，可以将LibFM文本格式的文件转换为二进制格式的文件。

&emsp;&emsp;./triple_format_to_libfm.pl -in ratings.dat -target 2 -delete_column 3 -separator "::"

&emsp;&emsp;例如：
&emsp;&emsp;将前面提到的电影数据集转换成二级制格式：
&emsp;&emsp;./convert --ifile ratings.dat.libfm --ofilex ratings.x --ofiley ratings.y

&emsp;&emsp;输出两个文件: 
&emsp;&emsp;（1）包含设计矩阵X即预测器变量的文件
&emsp;&emsp;（2）包含预测目标y的文件
&emsp;&emsp;建议，分别以.x和.y作为文件拓展名

##### 2.2.2.1转置数据（Transpose data）

&emsp;&emsp;使用转置设计矩阵（transposed design matrix）来学习MCMC和ALS。
&emsp;&emsp;如果您使用的是文本格式，libFm内部会自动转换这些数据。
&emsp;&emsp;如果您使用的是二进制格式，二进制格式中必须存在转置数据。
&emsp;&emsp;使用transpose工具，将设计矩阵x转换为二进制格式：

&emsp;&emsp;例如:转换上述提到的电影数据集：
&emsp;&emsp;./transpose --ifile ratings.x --ofile ratings.xt
&emsp;&emsp;输出为设计矩阵x的一个转置复制，建议以.xt作为结尾。

### 2.3 libFm
&emsp;&emsp;libFm工具从训练数据集（-train）和验证数据集（-test）中训练FM模型。

&emsp;&emsp;libFm有如下选项：

#### 2.3.1 强制参数

• 指定的第一个强制性参数—— -task 要么是分类 (-task c) 要么就是回归 (-任务 r)。

• 第二训练数据 (-train) 和测试数据 (-test) 必须存在。此处可以使用二进制文件，也可以使用libFm文本格式文件。

• 第三，分解机的维度需要用-dim来指定，由三个数字组成，
&emsp;&emsp;——来确定全局偏移是否要在模型中使用。
&emsp;&emsp;——来确定单向交互(one-way interactions)(为每个变量的偏移)即w是否要在模型中使用
&emsp;&emsp;——给出了用于成对相互作用的因素的个数，即k是

&emsp;&emsp;例如：一个FM，使用bias，1-way interactions，a factorization of k = 8 forpairwise interactions的回归任务——
&emsp;&emsp;/libFM -task r -train ml1m-train.libfm -test ml1m-test.libfm -dim ’1,1,8’

#### 2.3.2 可选参数

##### 2.3.2.1基本参数

• out︰ 训练完毕后，您可以将测试数据集的所有预测结果通过out写入指定的文件。Out-file 是文本格式，与测试数据集的行数相等，第i行的数据为第i个测试数据的结果。
请注意，对于分类，有积极类型的数据输出的是概率。
• rlog︰ 生成一个有关每次迭代的统计信息的日志文件。该文件是 使用制表符分隔字段CSV 格式。
请注意，它取决于哪些字段报道的学习方法。
• verbosity︰ 使用参数-详细级别 1，libFM 打印的详细信息。这是有用的检查是否正确，读取您的数据，并找出错误。

##### 2.3.2.1 高阶参数

**Grouping**
&emsp;&emsp;通过使用meta选项可以进行将输入变量group，grouping可以用来给ALS，MCMC，SGDA来确定更复杂的正则化模型。
&emsp;&emsp;每个group可以有一个单独的正则化参数。
&emsp;&emsp;为了使用group，元参数需要使用文本文件的文件名，和有很多输入变量和许多行一样。
&emsp;&emsp;每一行指定一个相应输入参数的group id。【需要注意的是】group的id需要是从0开始的数字。
&emsp;&emsp;例如：
&emsp;&emsp;例子1中的设计矩阵（一共7行，最大的id是6）的group文件，应该是这样的
&emsp;&emsp;表示的意义是：一共有三组，前两个变量 （设计矩阵中的列）有同组，第三和最后是同一组，第四至第六变量有同一组。
&emsp;&emsp;二进制数据和缓存
&emsp;&emsp;在2.2.2章节中提到，二进制文件中，设计矩阵以应以.x和目标以.y结尾，转置以.xt结尾。如果在libfm中使用二进制文件，那么不需要以这些格式结尾。

&emsp;&emsp;即：如果你有 compiled training (ml1m-train.x, ml1m-train.y,ml1m-train.xt) and 测试数据 (ml1m-test.x, ml1m-test.y, ml1m-test.xt) 
&emsp;&emsp;使用——
&emsp;&emsp;./libFM -task r -trainml1m-train -testml1m-test -dim ’1,1,8’

&emsp;&emsp;libFm会自动追加适当的扩展名，并为学习算法载入数据集

&emsp;&emsp;如果你的数据不适合进入内存，你可以指定libFM允许多大的文件允许保存在内存中
&emsp;&emsp;使用——
&emsp;&emsp;./libFM -task r -train ml1m-train -test ml1m-test -dim ’1,1,8’-cache_size 100000000
&emsp;&emsp;表示为100,000,000 Bytes (100 MB)的内存可以被.x或者.xt文件使用。

&emsp;&emsp;【注意】

&emsp;&emsp;.y文件通常完全地读入内存中。

&emsp;&emsp;如果没有指定参数cache-size，所有数据将都进入内存。
&emsp;&emsp;【注意】

&emsp;&emsp;只有当数据因为cache使用比读写内存慢很多的锁（harddisc）的时候而不适合进行内存，才使用caching。

&emsp;&emsp;Note: you should usecaching only if the data does not fit into memory because caching uses the harddisc which will be muchslower then memory access.

#### 2.3.3 学习方法

&emsp;&emsp;默认的学习方式是MCMC，因为MCMC是非常易于掌握的（没有学习速率，没有正则化项）
&emsp;&emsp;在libFM中你可以选择SGD,ALS, MCMC ， SGDA。对于所有这些方法，迭代次数（iter）都需要指定

##### 2.3.3.1 Stochastic Gradient Descent (SGD)

&emsp;&emsp;通过使用-method sgd参数，可以实现SGD学习方法，对于此方法，以下参数可以选择。
• -learn rate：SGD学习速率的步长，需是一个非零且postive的值
• -regular:正则化参数，需是0或者postive的值
&emsp;&emsp;对于SGD，你可以通过以下方法来确定正则化的值：
– One value (-regular value):所有的参数模型使用统一的正则化值
– Three values (-regular ’value0,value1,value2’):0-way interactions (w0) use value0 asregularization, 
1-way interactions (w) use value1 
pairwise ones (V ) use value2
– No value:使用-regular 0来表示没有指定正则化值
• -init stdev:标准偏差的正态分布，用于初始化V 的参数。在这里你应该使用一个非零的、 postive的值。

&emsp;&emsp;请慎重选择这些参数，预测质量很大程度上取决于对很好的选择。
&emsp;&emsp;例如：
&emsp;&emsp;./libFM -task r -train ml1m-train.libfm -test ml1m-test.libfm -dim ’1,1,8’ -iter 1000-method sgd -learn_rate 0.01 -regular ’0,0,0.01’ -init_stdev 0.1

##### 2.3.3.2 Alternating Least Squares (ALS)

&emsp;&emsp;通过使用-method als参数，可以实现SGD学习方法，对于此方法，以下参数可以选择。
• -regular:正则化参数，需是一个非零且postive的值
&emsp;&emsp;对于ALS可以使用以下方法来正则化:
– One value (-regular value):所有的参数模型使用统一的正则化值
– Three values (-regular ’value0,value1,value2’):0-way interactions (w0) use value0 asregularization, 
1-way interactions (w) use value1 
pairwise ones (V ) use value2
– Group specific values (-regular ’value0,value1g1,...,value1gm,value2g1,...,value2gm’):例如，对于m groups如果输入变量是grouped的，对于每个group，
1-way and 2-way interaction 每一个正则化值都被使用，那么有1+2m个正则化值，
– No value:使用-regular 0来表示没有指定正则化值

• -init stdev:标准偏差的正态分布，用于初始化V 的参数。在这里你应该使用一个非零的、 postive的值。
&emsp;&emsp;请慎重选择这些参数，预测质量很大程度上取决于对很好的选择。
&emsp;&emsp;例如：
&emsp;&emsp;./libFM -task r -train ml1m-train.libfm -test ml1m-test.libfm -dim ’1,1,8’ -iter 1000-method als -regular ’0,0,10’ -init_stdev 0.1

##### 2.3.3.3 Markov Chain Monte Carlo (MCMC)

&emsp;&emsp;通过使用-method mcmc参数，可以实现MCMC学习方法，对于此方法，以下参数可以选择。
• -init stdev:标准偏差的正态分布，用于初始化V 的参数。在这里你应该使用一个非零的、 postive的值。
&emsp;&emsp;请慎重选择这些参数，预测质量很大程度上取决于对很好的选择。
&emsp;&emsp;例如：
&emsp;&emsp;./libFM -task r -train ml1m-train.libfm -test ml1m-test.libfm -dim ’1,1,8’ -iter 1000-method mcmc -init_stdev 0.1

##### 2.3.3.4 Adaptive SGD (SGDA)

&emsp;&emsp;通过使用-method sgda参数，可以实现SGDA学习方法。当采用SGDA时，正则化值（每组和每层）会被自动找到。
&emsp;&emsp;你需要去指定一个有效的集合去调优正则化值。
• -validation:包含训练样本的数据集用作验证集合来调优正则化值。此数据集需要与训练数据集区分开。
• -learn rate:学习速率的步长，需是一个非零且postive的值
• -init stdev:标准偏差的正态分布，用于初始化V 的参数。在这里你应该使用一个非零的、 postive的值。

&emsp;&emsp;请慎重选择这些参数，预测质量很大程度上取决于对很好的选择。

&emsp;&emsp;例如：
&emsp;&emsp;./libFM -task r -train ml1m-train.libfm -test ml1m-test.libfm -dim ’1,1,8’ -iter 1000-method sgda -learn_rate 0.01 -init_stdev 0.1 -validation ml1m-val.libfm

### 2.4.块结构 (BS) 扩展

&emsp;&emsp;上图表示：
&emsp;&emsp;（a) LibFM 数据文件 （= 的设计矩阵 X 表示形式） 可能包含大块重复的图案。
&emsp;&emsp;（b） libFM 的BS 扩展允许使用更紧凑的表示数据文件来表示曾经描述过的重复图案，哪里会只是曾经描述了。（图改编自 [7]）

&emsp;&emsp;在相关背景下，在设计矩阵可能包含大块的重复的模式 （见图 1a）。 这可能导致设计矩阵非常大，以至于学习速度慢而且占用很多内存。
&emsp;&emsp;在libFM的BS扩展中，允许在设计矩阵中定义和利用块结构。BS数据类型取代传统的数据类型所用时间和所占内存都会成线性。
&emsp;&emsp;来自相关数据的大的设计矩阵的具体细节详情见[7]

### 2.4.1数据格式

&emsp;&emsp;BS 扩展允许定义块 （例如 B1、 B2、 B3 中图 1），在 libFM 中使用它们。
&emsp;&emsp;每个块定义包括︰
&emsp;&emsp;• 设计矩阵 （libFM 文件） 的块 (例如 XB1在图 1)。
&emsp;&emsp;• 从训练（或测试）case 映射到行中的块 （例如 φ 例B1在图 1)。
&emsp;&emsp;• 设计矩阵 中的可选分组（比较第 3.2.2 节） 。对于每个块，预计以下文件︰

#### 2.4.2使用BS数据来启动LibFm

&emsp;&emsp;使用--relation参数来传递命令行参数，假设已经定义了两块(rel.user andrel.item）则使用
&emsp;&emsp;./libFM -task r -train ml1m-train -test ml1m-test -dim ’1,1,8’ --relation rel.user,rel.item

&emsp;&emsp;注意:上面文件中列出的每一块都必须出现。(i.e. rel.user.x, rel.user.xt,rel.user.train, rel.user.test, (rel.user.groups), rel.item.x, rel.item.xt, etc.).

&emsp;&emsp;4.3在libFm中使用BS的注意事项

• BS 仅支持由 MCMC 和 ALS/CD。
• 甚至当使用 BS 时, --train ，--test参数是仍旧强制执行，文件必须是在此处指定。LibFM 文件通过--train ，--test可以有预测变量以及但也可能是 空。
  文件可以是二进制形式，可以是文本形式
• 在 BS 设计矩阵变量 id 的命名空间是不同的。
• 在BS文件中group的命名空间是不同的。每一个组文件可以有从0开始的组。 – overlaps are resolved the same way as with predictor ids.
• If no group files are passed, each block is automatically assumed to have a different group


### 2.5 许可证

<br>
<br>

## 3 fm的Python实现
&emsp;&emsp;[fm_python](https://github.com/jizhihui/fm_python)

<br>
<br>
<br>
<br>

githubgithubgithub


## Reference:
1. [分解机（Fatorization Machines推荐算法原理](https://www.cnblogs.com/pinard/p/6370127.html)
2. [推荐系统】Factorization Machine](https://blog.csdn.net/shenxiaolu1984/article/details/78740481)
3. [Factorization Machines in Python实现（没有成功）](https://github.com/coreylynch/pyFM)
4. [fm_python](https://github.com/jizhihui/fm_python)
4. [机器学习算法实现解析——libFM之libFM的训练过程概述](https://blog.csdn.net/google19890102/article/details/72866320)
5. [LibFM使用手册中文版](https://blog.csdn.net/Chloezhao/article/details/53462411)