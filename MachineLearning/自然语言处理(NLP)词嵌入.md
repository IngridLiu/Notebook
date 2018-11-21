# 词嵌入(word2vec)

<br>
<br>

## 1. 为何不采用 one-hot 向量

假设词典中不同词的数量（词典大小）为 N，每个词可以和从 0 到 N−1的连续整数一一对应。这些与词对应的整数叫做词的索引。 假设一个词的索引为 i，为了得到该词的 one-hot 向量表示，我们创建一个全 0 的长为 N的向量，并将其第 i位设成 1。这样一来，每个词就表示成了一个长度为 N的向量，可以直接被神经网络使用。

虽然 one-hot 词向量构造起来很容易，但通常并不是一个好选择。一个主要的原因是，one-hot 词向量无法准确表达不同词之间的相似度，例如我们常常使用的余弦相似度。对于向量 x,y∈Rd，它们的余弦相似度是它们之间夹角的余弦值。

![](https://upload-images.jianshu.io/upload_images/10947003-cdb3732e0bbeeed9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/600)

由于任何两个不同词的 one-hot 向量的余弦相似度都为 0，多个不同词之间的相似度难以通过 one-hot 向量准确地体现出来。

Word2vec 工具的提出正是为了解决上面这个问题 [1]。它将每个词表示成一个定长的向量，并使得这些向量能较好地表达不同词之间的相似和类比关系。Word2vec 工具包含了两个模型：跳字模型（skip-gram）[2] 和连续词袋模型（continuous bag of words，简称 CBOW）[3]。接下来让我们分别介绍这两个模型以及它们的训练方法。

## 2. 跳字模型(skip gram)

### 2.1 跳字模型介绍

跳字模型假设基于某个词来生成它在文本序列周围的词。举个例子，假设文本序列是“the”、“man”、“loves”、“his”和“son”。以“loves”作为中心词，设背景窗口大小为 2。如图 10.1 所示，跳字模型所关心的是，给定中心词“loves”，生成与它距离不超过 2 个词的背景词“the”、“man”、“his”和“son”的条件概率，即

P(``the",``man",``his",``son"∣``loves")

假设给定中心词的情况下，背景词的生成是相互独立的，那么上式可以改写成

P(``the"∣``loves")⋅P(``man"∣``loves")⋅P(``his"∣``loves")⋅P(``son"∣``loves")

![跳字模型关心给定中心词生成背景词的条件概率](https://upload-images.jianshu.io/upload_images/10947003-a3e4af76d81a84a4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/800)

在跳字模型中，每个词被表示成两个 d维向量用来计算条件概率。假设这个词在词典中索引为 i，当它为中心词时向量表示为 vi∈Rd，而为背景词时向量表示为 ui∈Rd。设中心词 wc在词典中索引为 c，背景词 wo在词典中索引为 o，给定中心词生成背景词的条件概率可以通过对向量内积做 softmax 运算而得到：

![](https://upload-images.jianshu.io/upload_images/10947003-a907cb2e53de64c6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/800)

其中词典索引集 V={0,1,…,|V|−1}。假设给定一个长度为 T的文本序列，设时间步 t的词为 w(t)。假设给定中心词的情况下背景词的生成相互独立，当背景窗口大小为 m时，跳字模型的似然函数即给定任一中心词生成所有背景词的概率

![](https://upload-images.jianshu.io/upload_images/10947003-2052ced03e044dad.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/800)

这里小于 1 和大于 T的时间步可以忽略。


[1] Word2vec 工具。https://code.google.com/archive/p/word2vec/

[2] Mikolov, T., Sutskever, I., Chen, K., Corrado, G. S., & Dean, J. (2013). Distributed representations of words and phrases and their compositionality. In Advances in neural information processing systems (pp. 3111-3119).

[3] Mikolov, T., Chen, K., Corrado, G., & Dean, J. (2013). Efficient estimation of word representations in vector space. arXiv preprint arXiv:1301.3781.

[4] [词嵌入（word2vec）](https://zh.gluon.ai/chapter_natural-language-processing/word2vec.html)