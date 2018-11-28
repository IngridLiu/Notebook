# 集成学习（Ensemble Learning）

<br>
<br>

&emsp;&emsp;提出问题：

&emsp;&emsp;1) 强学习算法：存在一个多项式时间的学习算法以识别一组概念，且识别的正确率很高。

&emsp;&emsp;2) 弱学习算法：识别一组概念的正确率仅比随机猜测略好。

&emsp;&emsp;3) 弱学习器与强学习器的等价问题。如果两者等价，只需找到一个比随机猜测略好的学习算法，就可以将其提升为强学习算法。

&emsp;&emsp;在机器学习的有监督学习算法中，我们的目标是学习出一个稳定的且在各个方面表现都较好的模型，但实际情况往往不这么理想，有时我们只能得到多个有偏好的模型（弱监督模型，在某些方面表现的比较好）。集成学习就是组合这里的多个弱监督模型以期得到一个更好更全面的强监督模型，集成学习潜在的思想是即便某一个弱分类器得到了错误的预测，其他的弱分类器也可以将错误纠正回来。

&emsp;&emsp;集成学习在各个规模的数据集上都有很好的策略。

&emsp;&emsp;**数据集大：划分成多个小数据集，学习多个模型进行组合**

&emsp;&emsp;**数据集小：利用Bootstrap方法进行抽样，得到多个数据集，分别训练多个模型再进行组合.**

<br>

&emsp;&emsp;先说一下bootstrap，bootstrap也称为自助法，它是一种有放回的抽样方法，目的为了得到统计量的分布以及置信区间。具体步骤如下

&emsp;&emsp;- 采用重抽样方法（有放回抽样）从原始样本中抽取一定数量的样本

&emsp;&emsp;- 根据抽出的样本计算想要得到的统计量T

&emsp;&emsp;- 重复上述N次（一般大于1000），得到N个统计量T

&emsp;&emsp;- 根据这N个统计量，即可计算出统计量的置信区间

<br>

## 1. Bagging

&emsp;&emsp;Bagging即套袋法，其算法过程如下：

&emsp;&emsp;（1）从原始样本集中抽取训练集。每轮从原始样本集中使用Bootstraping的方法抽取n个训练样本（在训练集中，有些样本可能被多次抽取到，而有些样本可能一次都没有被抽中）。共进行k轮抽取，得到k个训练集。（k个训练集之间是相互独立的）

&emsp;&emsp;（2）每次使用一个训练集得到一个模型，k个训练集共得到k个模型。（注：这里并没有具体的分类算法或回归方法，我们可以根据具体问题采用不同的分类或回归方法，如决策树、感知器等）

&emsp;&emsp;（3）对分类问题：将上步得到的k个模型采用投票的方式得到分类结果；对回归问题，计算上述模型的均值作为最后的结果。（所有模型的重要性相同）

<br>

## 2. Boosting

&emsp;&emsp;AdaBoosting方式每次使用的是全部的样本，每轮训练改变样本的权重。下一轮训练的目标是找到一个函数f来拟合上一轮的残差。当残差足够小或者达到设置的最大迭代次数则停止。Boosting会减小在上一轮训练正确的样本的权重，增大错误样本的权重。（对的残差小，错的残差大）。

&emsp;&emsp;之前提到过的GBDT（Gradient Boost Decision Tree)也是一种Boosting的方法，与AdaBoost不同，GBDT每一次的计算是为了减少上一次的残差，GBDT在残差减少（负梯度）的方向上建立一个新的模型。

&emsp;&emsp;Adaboost, GBDT, XGBOOST;

### 2.1 Bagging与Boosting二者之间的区别

&emsp;&emsp;Bagging和Boosting的区别：

&emsp;&emsp;(1)样本选择上：

&emsp;&emsp;Bagging：训练集是在原始集中有放回选取的，从原始集中选出的各轮训练集之间是独立的。

&emsp;&emsp;Boosting：每一轮的训练集不变，只是训练集中每个样例在分类器中的权重发生变化。而权值是根据上一轮的分类结果进行调整。

&emsp;&emsp;(2)样例权重：

&emsp;&emsp;Bagging：使用均匀取样，每个样例的权重相等

&emsp;&emsp;Boosting：根据错误率不断调整样例的权值，错误率越大则权重越大。

&emsp;&emsp;(3)预测函数：

&emsp;&emsp;Bagging：所有预测函数的权重相等。

&emsp;&emsp;Boosting：每个弱分类器都有相应的权重，对于分类误差小的分类器会有更大的权重。

&emsp;&emsp;(4)并行计算：

&emsp;&emsp;Bagging：各个预测函数可以并行生成

&emsp;&emsp;Boosting：各个预测函数只能顺序生成，因为后一个模型参数需要前一轮模型的结果。

&emsp;&emsp;(5)bagging是减少variance，而boosting是减少bias:



<br>

## 3. Stacking

&emsp;&emsp;Stacking方法是指训练一个模型用于组合其他各个模型。首先我们先训练多个不同的模型，然后把之前训练的各个模型的输出为输入来训练一个模型，以得到一个最终的输出。理论上，Stacking可以表示上面提到的两种Ensemble方法，只要我们采用合适的模型组合策略即可。但在实际中，我们通常使用logistic回归作为组合策略。

&emsp;&emsp;如下图，先在整个训练数据集上通过bootstrap抽样得到各个训练集合，得到一系列分类模型，称之为Tier 1分类器（可以采用交叉验证的方式学习），然后将输出用于训练Tier 2 分类器。

![](https://upload-images.jianshu.io/upload_images/10947003-4843ee97f703a7e7.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/600)

<br>

&emsp;&emsp;在算法学习的时候，通常在bias和variance之间要有一个权衡。bias与variance的关系如下图，因而模型要想达到最优的效果，必须要兼顾bias和variance，也就是要采取策略使得两者比较平衡。

![](https://upload-images.jianshu.io/upload_images/10947003-39fd4ef1724647a4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/600)

&emsp;&emsp;从算法来看，Bagging关注的是多个基模型的投票组合，保证了模型的稳定，因而每一个基模型就要相对复杂一些以降低偏差（比如每一棵决策树都很深）；而Boosting采用的策略是在每一次学习中都减少上一轮的偏差，因而在保证了偏差的基础上就要将每一个基分类器简化使得方差更小。

<br>
<br>
<br>
<br>

##Reference:

1.[集成学习（Ensemble Learning)](https://zhuanlan.zhihu.com/p/27689464)

2.[Bagging和Boosting的区别（面试准备）](https://www.cnblogs.com/earendil/p/8872001.html)