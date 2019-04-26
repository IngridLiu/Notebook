# 词向量模型-Glove

<br>
<br>

## 1. Glove的介绍

&emsp;&emsp;Glove是2014年由Stanford团队发表的。Glove的全称叫Global Vectors for Word Representation，它是一个基于全局词频统计（count-based & overall statistics）的词表征（word representation）工具，它可以把一个单词表达成一个由实数组成的向量，这些向量捕捉到了单词之间的一些语义特征，比如相似性（similarity）、类比性（analogy）等。我们通过对向量的运算，比如欧几里得距离或者cosine相似度可以计算出两个单词之间的语义相似度。

<br>

## 2. Glove的实现K

&emsp;&emsp;Glove的实现分为以下三步：

&emsp;&emsp;**（1）根据语料库（corpus）构建一个共现矩阵(Co-ocurrence Matrix) X。**

&emsp;&emsp;共现矩阵中的每一个元素X_ij代表单词i和上下文单词j在特定大小的上下文窗口（context window）内共同出现的次数。一般而言，这个次数的最小单位是1，但是Glove不这么认为：它根据两个单词在上下文窗口的距离d，提出了一个衰减函数（decreasing weighting）：decay = 1/d用于计算权重，也就是说距离越远的两个单词所占总计数（total count）的权重越小。

> In all cases we use a decreasing weighting function, so that word pairs that are d words apart contribute 1/d to the total count.

&emsp;&emsp;**（2）构建词向量（Word Vector）和共现矩阵（Co-ocurrence Matrix）之间的近似关系，论文的作者提出以下的公式可以近似地表达两者之间地关系：**

![](https://upload-images.jianshu.io/upload_images/10947003-d98749e561de7f1a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

&emsp;&emsp;其中，w_i和w_j是我们最终要求解的词向量；b_i和b_j分别是两个词向量的bias term。

&emsp;&emsp;**（3）有了公式1之后我们就可以构造它的loss function了：**K

![](https://upload-images.jianshu.io/upload_images/10947003-46f44dd5744f1c76.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

&emsp;&emsp;这个loss function的基本形式就是最简单的mean square loss，只不过在此基础上加了一个权重函数f(x_ij)，，那么这个函数起了什么作用，为什么要添加这个函数呢？我们知道在一个语料库中，肯定存在很多单词他们在一起出现的次数是很多的（frequent co-occurrences），那么我们希望：

&emsp;&emsp;① 这些单词的权重要大于那些很少在一起出现的单词（rate co-currences），所以这个函数是非递减函数（non-decreasing）；

&emsp;&emsp;② 但我们也不希望这个权重过大（overweighted），当达到一定程度之后应该不再增加；

&emsp;&emsp;③ 如果两个单词没有在一起出现，也就是X_ij=0，那么他们应该不参与到loss function的计算当中去，也就是f(x)要满足f(0)=0;

&emsp;&emsp;满足以上两个条件的函数有很多，作者采用了如下形式的分段函数：

![](https://upload-images.jianshu.io/upload_images/10947003-74a5552a11f4ae80.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

&emsp;&emsp;这个函数图像如下所示：

![](https://i.imgur.com/zE6t1ig.jpg)

&emsp;&emsp;这篇论文中的所有实验，α的取值都是0.75，而x_max取值都是100。

<br>

## 3. Glove训练

&emsp;&emsp;虽然很多人声称GloVe是一种无监督（unsupervised learing）的学习方式（因为它确实不需要人工标注label），但其实它还是有label的，这个label就是公式2中的log(X_ij)，而公式2中的向量w和~w就是要不断更新/学习的参数，所以本质上它的训练方式跟监督学习的训练方法没什么不一样，都是基于梯度下降的。

&emsp;&emsp;具体地，这篇论文里地实验是这么做地：采用了AdaGrad地梯度下降算法，对矩阵X中所有的非零元素进行随机采样，学习曲率（learning rate）设为0.05，在vector size小于300的情况下迭代了50次，其他大小的vectors上迭代了100次，直至收敛。最终学习得到的是两个vector是w和~w，因为X是对称的（symmetric），所以从原理上讲w和~w是也是对称的，他们唯一的区别是初始化的值不一样，而导致最终的值不一样。所以这两者其实是等价的，都可以当成最终的结果来使用。但是为了提高鲁棒性，我们最终会选择两者之和w+~w作为最终的vector（两者的初始化不同相当于加了不同的随机噪声，所以能提高鲁棒性）。在训练了400亿个token组成的语料后，得到的实验结果如下图所示：

![](https://i.imgur.com/X6eVUJJ.jpg)

&emsp;&emsp;这个图一共采用了三个指标：语义准确度，语法准确度以及总体准确度。那么我们不难发现Vector Dimension在300时能达到最佳，而context Windows size大致在6到10之间。

<br>

## 4. Glove与LSA、word2vec的比较

&emsp;&emsp;LSA（Latent Semantic Analysis）是一种比较早的count-based的词向量表征工具，它也是基于co-occurance matrix的，只不过采用了基于奇异值分解（SVD）的矩阵分解技术对大矩阵进行降维，而我们知道SVD的复杂度是很高的，所以它的计算代价比较大。还有一点是它对所有单词的统计权重都是一致的。而这些缺点在GloVe中被一一克服了。而word2vec最大的缺点则是没有充分利用所有的语料，所以GloVe其实是把两者的优点结合了起来。从这篇论文给出的实验结果来看，GloVe的性能是远超LSA和word2vec的，但网上也有人说GloVe和word2vec实际表现其实差不多。

## 5. 公式推导

见：[GloVe详解](http://www.fanyeong.com/2018/02/19/glove-in-detail/)



<br>
<br>
<br>
<br>

## Reference:

1. [动手学深度学习第十七课：GloVe、fastText和使用预训练的词向量](https://www.youtube.com/watch?v=ioSnNLZSQq0)

2. [GloVe详解](http://www.fanyeong.com/2018/02/19/glove-in-detail/)
