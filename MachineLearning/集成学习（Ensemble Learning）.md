# 集成学习（Ensemble Learning）

<br>
<br>

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

&emsp;&emsp;Bagging是bootstrap aggregating的简写。

&emsp;&emsp;在Bagging方法中，利用bootstrap方法从整体数据集中采取有放回抽样得到N个数据集，在每个数据集上学习出一个模型，最后的预测结果利用N个模型的输出得到，具体地：分类问题采用N个模型预测投票的方式，回归问题采用N个模型预测平均的方式。

&emsp;&emsp;例如随机森林（Random Forest）就属于Bagging。随机森林简单地来说就是用随机的方式建立一个森林，森林由很多的决策树组成，随机森林的每一棵决策树之间是没有关联的。

&emsp;&emsp;在我们学习每一棵决策树的时候就需要用到Bootstrap方法。在随机森林中，有两个随机采样的过程：对输入数据的行（数据的数量）与列（数据的特征）都进行采样。对于行采样，采用有放回的方式，若有N个数据，则采样出N个数据（可能有重复），这样在训练的时候每一棵树都不是全部的样本，相对而言不容易出现overfitting；接着进行列采样从M个feature中选择出m个（m<<M）。最近进行决策树的学习。

&emsp;&emsp;预测的时候，随机森林中的每一棵树的都对输入进行预测，最后进行投票，哪个类别多，输入样本就属于哪个类别。这就相当于前面说的，每一个分类器（每一棵树）都比较弱，但组合到一起（投票）就比较强了。

<br>

## 2. Boosting

&emsp;&emsp;提升方法（Boosting）是一种可以用来减小监督学习中偏差的机器学习算法。主要也是学习一系列弱分类器，并将其组合为一个强分类器。Boosting中有代表性的是AdaBoost（Adaptive boosting）算法：刚开始训练时对每一个训练例赋相等的权重，然后用该算法对训练集训练t轮，每次训练后，对训练失败的训练例赋以较大的权重，也就是让学习算法在每次学习以后更注意学错的样本，从而得到多个预测函数。具体可以参考《统计学习方法》。

&emsp;&emsp;之前提到过的GBDT（Gradient Boost Decision Tree)也是一种Boosting的方法，与AdaBoost不同，GBDT每一次的计算是为了减少上一次的残差，GBDT在残差减少（负梯度）的方向上建立一个新的模型。

### 2.1 Bagging与Boosting

&emsp;&emsp;Bagging和Boosting采用的都是采样-学习-组合的方式，但在细节上有一些不同，如

&emsp;&emsp;**Bagging中每个训练集互不相关，也就是每个基分类器互不相关，而Boosting中训练集要在上一轮的结果上进行调整，也使得其不能并行计算**

&emsp;&emsp;**Bagging中预测函数是均匀平等的，但在Boosting中预测函数是加权的**

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