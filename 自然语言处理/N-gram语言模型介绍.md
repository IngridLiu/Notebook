# N-gram语言模型

<br>
<br>

## 1. 什么是n-gram模型

&emsp;&emsp;N-Gram是一种基于统计语言模型的算法。它的基本思想是将文本里面的内容按照字节进行大小为N的滑动窗口操作，形成了长度是N的字节片段序列。

&emsp;&emsp;每一个字节片段称为gram，对所有gram的出现频度进行统计，并且按照事先设定好的阈值进行过滤，形成关键gram列表，也就是这个文本的向量特征空间，列表中的每一种gram就是一个特征向量维度。

&emsp;&emsp;该模型基于这样一种假设，第N个词的出现只与前面N-1个词相关，而与其它任何词都不相关，整句的概率就是各个词出现概率的乘积。这些概率可以通过直接从语料中统计N个词同时出现的次数得到。常用的是二元的Bi-Gram和三元的Tri-Gram。

&emsp;&emsp;如果我们有一个由 m 个词组成的序列（或者说一个句子），我们希望算得概率 

![](https://www.zhihu.com/equation?tex=p%28w_%7B1%7D%2Cw_%7B2%7D%2C...%2Cw_%7Bm%7D%29)

&emsp;&emsp;根据链式规则，可得

![](https://www.zhihu.com/equation?tex=p%28w_%7B1%7D%2Cw_%7B2%7D%2C...%2Cw_%7Bm%7D%29%3Dp%28w_%7B1%7D%29%2Ap%28w_%7B2%7D%7Cw_%7B1%7D%29%2Ap%28w_%7B3%7D%7Cw_%7B1%7D%2Cw_%7B2%7D%29.....p%28w_%7Bm%7D%7Cw_%7B1%7D%2C..%2Cw_%7Bm-1%7D%29)

&emsp;&emsp;这个概率显然并不好算，不妨利用马尔科夫链的假设，即当前这个词仅仅跟前面几个有限的词相关，因此也就不必追溯到最开始的那个词，这样便可以大幅缩减上述算式的长度。即:

![](https://www.zhihu.com/equation?tex=p%28w_%7B1%7D%2Cw_%7B2%7D%2C...%2Cw_%7Bm%7D%29%3Dp%28w_%7Bi%7D%7Cw_%7Bi-n%2B1%2C+...%2Cw_%7Bi-1%7D%7D%29)

&emsp;&emsp;下面给出一元模型，二元模型，三元模型的定义：

&emsp;&emsp;当 n=1, 一个一元模型（unigram model)即为 ：

![](https://pic1.zhimg.com/80/v2-4e5bacfab55c6fc21990be89e3c84e14_hd.jpg)

&emsp;&emsp;当 n=2, 一个二元模型（bigram model)即为 ：

![](https://pic2.zhimg.com/80/v2-d45c62f548c4da5d47a904a09ba20159_hd.jpg)

&emsp;&emsp;当 n=3, 一个三元模型（trigram model)即为:

![](https://pic1.zhimg.com/80/v2-53fd4958fb85de0afdae15b1af1861ac_hd.jpg)

&emsp;&emsp;在给定的训练语料中，利用贝叶斯定理，将上述的条件概率值（因为一个句子出现的概率都转变为右边条件概率值相乘了）都统计计算出来即可。下面会给出具体例子讲解。这里先给出公式：

![](https://pic1.zhimg.com/80/v2-507fac3a49357eed0fbd4cd6fb8ce6b0_hd.jpg)

&emsp;&emsp;对第一个进行解释，后面同理,如下：

![](https://www.zhihu.com/equation?tex=p%28w_%7Bi%7D%7Cp%28w_%7Bi-1%7D%29%29%3Dp%28w_%7Bi%7D%2Cw_%7Bi-1%7D%29%2Fp%28w_%7Bi-1%7D%29%3D%28count%28w_%7Bi%7D%2Cw_%7Bi-1%7D%29%2Fcount%28ALLword%29%29%2F%28count%28w_%7Bi-1%7D%29%2Fcount%28ALLword%29%29%3Dcount%28w_%7Bi%7D%2Cw_%7Bi-1%7D%29%2Fcount%28w_%7Bi-1%7D%29)

## 2. 二元语言模型判断句子是否合理

&emsp;&emsp;下面例子来自于：[自然语言处理中的N-Gram模型详解 - 白马负金羁 - CSDN博客](https://link.zhihu.com/?target=http%3A//blog.csdn.net/baimafujinji/article/details/51281816)和《北京大学 常宝宝 以及 The University of Melbourne “Web Search and Text Analysis” 课程的幻灯片素材》

&emsp;&emsp;假设现在有一个语料库，我们统计了下面的一些词出现的数量

![](https://pic1.zhimg.com/80/v2-43745e5526b6eb8341a896c8abe8c640_hd.jpg)

&emsp;&emsp;下面的这些概率值作为已知条件：

![](https://pic1.zhimg.com/80/v2-a7c0d77143e0c997abd45e1535eaeb8c_hd.jpg)

&emsp;&emsp;p(want|<s>) = 0.25

&emsp;&emsp;下面这个表给出的是基于Bigram模型进行计数之结果

![](https://pic3.zhimg.com/80/v2-d9d0700496b79f4456776df80856f37a_hd.jpg)

&emsp;&emsp;例如，其中第一行，第二列 表示给定前一个词是 “i” 时，当前词为“want”的情况一共出现了827次。据此，我们便可以算得相应的频率分布表如下

![](https://pic2.zhimg.com/80/v2-e53505cae4d3fa21d29f1ff2c267eb49_hd.jpg)

&emsp;&emsp;比如说，我们就以表中的p(eat|i)=0.0036这个概率值讲解，从表一得出“i”一共出现了2533次，而其后出现eat的次数一共有9次，p(eat|i)=p(eat,i)/p(i)=count(eat,i)/count(i)=9/2533 = 0.0036

&emsp;&emsp;下面我们通过基于这个语料库来判断s1=“<s> i want english food</s>” 与s2 = "<s> want i english food</s>"哪个句子更合理：通过例子来讲解是最人性化的，我在网上找了这么久发现这个例子最好：

&emsp;&emsp;首先来判断p(s1)

P(s1)=P(i|<s>)P(want|i)P(english|want)P(food|english)P(</s>|food)

=0.25×0.33×0.0011×0.5×0.68=0.000031

&emsp;&emsp;再来求p(s2)？

P(s2)=P(want|<s>)P(i|want)P(english|want)P(food|english)P(</s>|food)

=0.25*0.0022*0.0011*0.5*0.68 = 0.00000002057

&emsp;&emsp;通过比较我们可以明显发现0.00000002057<0.000031,也就是说s1= "i want english food</s>"更像人话。

&emsp;&emsp;再深层次的分析，我们可以看到这两个句子的概率的不同，主要是由于顺序i want还是want i的问题，根据我们的直觉和常用搭配语法，i want要比want i出现的几率要大很多。所以两者的差异，第一个概率大，第二个概率小，也就能说的通了。

<br>

## N-Gram模型实现：

&emsp;&emsp;sklearn库中的CountVectorizer 有一个参数ngram_range，如果赋值为(2,2)则为Bigram，当然使用语言模型会大大增加我们字典的大小。

```python
# N-gram语言模型
ram_range=(1,1) # 表示 unigram
ngram_range=(2,2)   # 表示 bigram,
ngram_range=(3,3)   # 表示 thirgram
from sklearn.feature_extraction.text import CountVectorizer
import pandas as pd
import jieba

data = ["为了祖国，为了胜利，向我开炮！向我开炮！",
        "记者：你怎么会说出那番话",
        "我只是觉得，对准我自己打"]
data = [' '.join(jieba.lcut(e)) for e in data]  # 分词，并用" "连接
vector = CountVectorizer(min_df=1, ngram_range=(2, 2))  # bigram
X = vector.fit_transform(data)  # 将分词好的文本转换为矩阵
print(vector.vocabulary_)   # 得到特征
print(X)    # (句子下标, 单词特征下标)   频数
ngram_df = pd.DataFrame(X.toarray(), columns = vector.get_feature_names())   # to DataFrame
print(ngram_df.head())
```



<br>
<br>
<br>
<br>

## Reference:

1.[N-gram语言模型简单介绍](https://www.cnblogs.com/wzm-xu/p/4229819.html)

2.[自然语言处理中N-Gram模型介绍](https://zhuanlan.zhihu.com/p/32829048)