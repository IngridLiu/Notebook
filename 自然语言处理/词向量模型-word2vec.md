# 词向量模型-word2vec

<br>
<br>
<br>
<br>

## 1. 词向量基础

## 1.1 One-hot Representation

&emsp;&emsp;词向量的热独（One-hot Representation）表示中，使用的词向量的维度为整个词汇表的大小，对于每一个具体的词汇表中的词，将对应的位置置为1。比如我们有下面的5个词组成的词汇表，词"Queen"的序号为2， 那么它的词向量就是(0,1,0,0,0)。同样的道理，词"Woman"的词向量就是(0,0,0,1,0)。这种词向量的编码方式我们一般叫做1-of-N representation或者one hot representation.

![](https://images2015.cnblogs.com/blog/1042406/201707/1042406-20170713145606275-2100371803.png)

&emsp;&emsp;One hot representation用来表示词向量非常简单，但是却有很多问题。最大的问题是我们的词汇表一般都非常大，比如达到百万级别，这样每个词都用百万维的向量来表示简直是内存的灾难。

## 1.2 Distributed Representation

&emsp;&emsp;Distributed representation可以解决One hot representation的问题，它的思路是通过训练，将每个词都映射到一个较短的词向量上来。所有的这些词向量就构成了向量空间，进而可以用普通的统计学的方法来研究词与词之间的关系。这个较短的词向量维度一般需要我们在训练时自己来指定。

&emsp;&emsp;比如下图我们将词汇表里的词用"Royalty","Masculinity", "Femininity"和"Age"4个维度来表示，King这个词对应的词向量可能是(0.99,0.99,0.05,0.7)。当然在实际情况中，我们并不能对词向量的每个维度做一个很好的解释。

![](https://images2015.cnblogs.com/blog/1042406/201707/1042406-20170713150625759-1047275185.png)

&emsp;&emsp;我们将king这个词从一个可能非常稀疏的向量坐在的空间，映射到现在这个四维向量所在的空间，必须满足以下性质：

&emsp;&emsp;（1）这个映射是单设（不懂的概念自行搜索）；

&emsp;&emsp;（2）映射之后的向量不会丢失之前的那种向量所含的信息。

&emsp;&emsp;这个过程称为word embedding（词嵌入），即将高维词向量嵌入到一个低维空间。

![](https://upload-images.jianshu.io/upload_images/9285151-548de7208a382a0c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/468/format/webp)

&emsp;&emsp;有了用Distributed Representation表示的较短的词向量，我们就可以较容易的分析词之间的关系了，比如我们将词的维度降维到2维，有一个有趣的研究表明，用下图的词向量表示我们的词时，我们可以发现：

![](https://upload-images.jianshu.io/upload_images/9285151-48358f3362496684.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/244/format/webp)



![](https://images2015.cnblogs.com/blog/1042406/201707/1042406-20170713151608181-1336632086.png)

<br>

## 2. word2vec

&emsp;&emsp;2013年，Google团队发表了word2vec工具。word2vec工具，主要包含两个模型：连续词袋模型（continuous bag of words，简称CBOW）和跳字模型（skip-gram），以及两种高效训练的方法：负采样（negative samplint)和层次softmax（hierachical softmax）。值得一提的是，word2vec词向量可以很好的

## 2.1 CBOW与Skip-Gram用于神经网络语言模型

&emsp;&emsp;CBOW模型的训练输入是某一个特征词的上下文相关的词对应的词向量，而输出就是这特定的一个词的词向量。

&emsp;&emsp;Skip-Gram模型和CBOW的思路是反着来的，即输入是特定的一个词的词向量，而输出是特定词对应的上下文词向量。

&emsp;&emsp;CBOW对小型数据库比较合适，而Skip-Gram在大型语料中表现更好。

![CBOW模型](https://upload-images.jianshu.io/upload_images/9285151-bf3d31fd22025027.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/421/format/webp)

![Skip-Gram模型](https://upload-images.jianshu.io/upload_images/9285151-fca1fdda41d6d422.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/462/format/webp)

### 2.1.1 CBOW（Continuous Bag-of-Words）

&emsp;&emsp;** CBOW模型的训练输入是某一特征词的上下文相关的词对应的词向量，而输出就是这特定的一个词的词向量。**比如下面这段话，我们的上下文大小取值为4，特定的这个词是"Learning"，也就是我们需要的输出词向量,上下文对应的词有8个，前后各4个，这8个词是我们模型的输入。由于CBOW使用的是词袋模型，因此这8个词都是平等的，也就是不考虑他们和我们关注的词之间的距离大小，只要在我们上下文之内即可。

![](https://images2015.cnblogs.com/blog/1042406/201707/1042406-20170713152436931-1817493891.png)

&emsp;&emsp;CBOW的训练模型如图所示：

![](https://upload-images.jianshu.io/upload_images/9285151-21157b859f9f3b2b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/518/format/webp)

&emsp;&emsp;1 输入层：上下文单词的onehot.  {假设单词向量空间dim为V，上下文单词个数为C}

&emsp;&emsp;2 所有onehot分别乘以共享的输入权重矩阵W. {VN矩阵，N为自己设定的数，初始化权重矩阵W}

&emsp;&emsp;3 所得的向量 {因为是onehot所以为向量} 相加求平均作为隐层向量, size为1N.

&emsp;&emsp;4 乘以输出权重矩阵W' {NV}

&emsp;&emsp;5 得到向量 {1V} 激活函数处理得到V-dim概率分布  {PS: 因为是onehot嘛，其中的每一维斗代表着一个单词}

&emsp;&emsp;6 概率最大的index所指示的单词为预测出的中间词（target word）与true label的onehot做比较，误差越小越好（根据误差更新权重矩阵）

&emsp;&emsp;所以，需要定义loss function（一般为交叉熵代价函数），采用梯度下降算法更新W和W'。训练完毕后，输入层的每个单词与矩阵W相乘得到的向量的就是我们想要的词向量（word embedding），这个矩阵（所有单词的word embedding）也叫做look up table（其实聪明的你已经看出来了，其实这个look up table就是矩阵W自身），也就是说，任何一个单词的onehot乘以这个矩阵都将得到自己的词向量。有了look up table就可以免去训练过程直接查表得到单词的词向量了。

&emsp;&emsp;举个例子：

![](https://upload-images.jianshu.io/upload_images/9285151-e293f7bb529f5e55.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/720/format/webp)

&emsp;&emsp;窗口大小是2，表示选取coffe前面两个单词和后面两个单词，作为input词。

![](https://upload-images.jianshu.io/upload_images/9285151-a119b8c935b22164.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/720/format/webp)

&emsp;&emsp;假设我们此时得到的概率分布已经达到了设定的迭代次数，那么现在我们训练出来的look up table应该为矩阵W。即，任何一个单词的one-hot表示乘以这个矩阵都将得到自己的word embedding。

### 2.1.2 Skip-Gram

&emsp;&emsp;Skip-Gram模型和CBOW的思路是反着来的，即输入是特定的一个词的词向量，而输出是特定词对应的上下文词向量。还是上面的例子，我们的上下文大小取值为4， 特定的这个词"Learning"是我们的输入，而这8个上下文词是我们的输出。

&emsp;&emsp;这样我们这个Skip-Gram的例子里，我们的输入是特定词， 输出是softmax概率排前8的8个词，对应的Skip-Gram神经网络模型输入层有1个神经元，输出层有词汇表大小个神经元。隐藏层的神经元个数我们可以自己指定。通过DNN的反向传播算法，我们可以求出DNN模型的参数，同时得到所有的词对应的词向量。这样当我们有新的需求，要求出某1个词对应的最可能的8个上下文词时，我们可以通过一次DNN前向传播算法得到概率大小排前8的softmax概率对应的神经元所对应的词即可。

### 2.1.3 CBOW（Continuous Bag-of-Words）和Skip-Gram的模型的

&emsp;&emsp;CBOW模型适合训练数据量较少的情况。

&emsp;&emsp;skip-gram 方法应用更广泛（训练数据较大时候效果比CBOW更好一点）。

<br>

### 2.2 近似训练法

#### 2.2.1 基于层序softmax（Hierarchical Softmax）的模型



#### 2.2.2 基于负采样(Negative Sampling)的模型

&emsp;&emsp;既然名字叫Negative Sampling（负采样），那么肯定使用了采样的方法。采样的方法有很多种，比如之前讲到的大名鼎鼎的MCMC。我们这里的Negative Sampling采样方法并没有MCMC那么复杂。

&emsp;&emsp;比如我们有一个训练样本，中心词是w,它周围上下文共有2c个词，记为context(w)。由于这个中心词w,的确和context(w)相关存在，因此它是一个真实的正例。通过Negative Sampling采样，我们得到neg个和w不同的中心词wi,i=1,2,..neg，这样context(w)和wi就组成了neg个并不真实存在的负例。利用这一个正例和neg个负例，我们进行二元逻辑回归，得到负采样对应每个词wi对应的模型参数θi，和每个词的词向量。

&emsp;&emsp;从上面的描述可以看出，Negative Sampling由于没有采用霍夫曼树，每次只是通过采样neg个不同的中心词做负例，就可以训练模型，因此整个过程要比Hierarchical Softmax简单。


## 3. 词向量实现

```python
# word2vec
from gensim.models import Word2Vec
import numpy as np

data = ["I love deep learning","I love studying","I want to travel"]
#词频少于min_count次数的单词会被丢弃掉
#size指特征向量的维度为50
#workers参数控制训练的并行数
train_w2v = Word2Vec(data, min_count=5, size=50, workers=4)
avg_data = []
for row in data:
    vec = np.zeros(50)
    count = 0
    for word in row:
        try:
            vec += train_w2v[word]
            count += 1
        except:
            pass
    avg_data.append(vec/count)
print(avg_data)
```

### 3.1 gensim下使用Word2vec参数说明：

&emsp;&emsp;用gensim函数库训练Word2Vec模型有很多配置参数。这里对gensim文档的Word2Vec函数的参数说明进行翻译。

&emsp;&emsp;class gensim.models.word2vec.Word2Vec(sentences=None,size=100,alpha=0.025,window=5, min_count=5, max_vocab_size=None, sample=0.001,seed=1, workers=3,min_alpha=0.0001, sg=0, hs=0, negative=5, cbow_mean=1, hashfxn=<built-in function hash>,iter=5,null_word=0, trim_rule=None, sorted_vocab=1, batch_words=10000)

&emsp;&emsp;参数：

· sentences：可以是一个list，对于大语料集，建议使用BrownCorpus,Text8Corpus或LineSentence构建。

· sg： 用于设置训练算法，默认为0，对应CBOW算法；sg=1则采用skip-gram算法。

· size：是指特征向量的维度，默认为100。大的size需要更多的训练数据,但是效果会更好. 推荐值为几十到几百。

· window：表示当前词与预测词在一个句子中的最大距离是多少

· alpha: 是学习速率

· seed：用于随机数发生器。与初始化词向量有关。

· min_count: 可以对字典做截断. 词频少于min_count次数的单词会被丢弃掉, 默认值为5

· max_vocab_size: 设置词向量构建期间的RAM限制。如果所有独立单词个数超过这个，则就消除掉其中最不频繁的一个。每一千万个单词需要大约1GB的RAM。设置成None则没有限制。

· sample: 高频词汇的随机降采样的配置阈值，默认为1e-3，范围是(0,1e-5)

· workers参数控制训练的并行数。

· hs: 如果为1则会采用hierarchical softmax技巧。如果设置为0（defaut），则negative sampling会被使用。

· negative: 如果>0,则会采用negativesamping，用于设置多少个noise words

· cbow_mean: 如果为0，则采用上下文词向量的和，如果为1（defaut）则采用均值。只有使用CBOW的时候才起作用。

· hashfxn： hash函数来初始化权重。默认使用python的hash函数

· iter： 迭代次数，默认为5

· trim_rule： 用于设置词汇表的整理规则，指定那些单词要留下，哪些要被删除。可以设置为None（min_count会被使用）或者一个接受()并返回RU·E_DISCARD,uti·s.RU·E_KEEP或者uti·s.RU·E_DEFAU·T的函数。

· sorted_vocab： 如果为1（defaut），则在分配word index 的时候会先对单词基于频率降序排序。

· batch_words：每一批的传递给线程的单词的数量，默认为10000

<br>

## 3. Word2Vec优缺点：

优点：

（1）

缺点：

（1）context 很小，没有使用全局的cooccur，所以实际上对cooccur的利用很少。


<br>
<br>

## Reference:

1. [通俗理解word2vec](https://www.jianshu.com/p/471d9bfbd72f)

2. [word2vec原理(二) 基于Hierarchical Softmax的模型](http://www.cnblogs.com/pinard/p/7243513.html)

3. [word2vec原理(三) 基于Negative Sampling的模型](https://www.cnblogs.com/pinard/p/7249903.html)

4. [动手学深度学习第十六课：词向量（word2vec）](https://www.youtube.com/watch?v=C4X0Cb5_FSo)

5. [word2vec and glove优缺点](https://blog.csdn.net/u012879957/article/details/82735057)