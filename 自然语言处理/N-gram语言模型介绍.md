# N-gram语言模型

N-gram语言模型是一种基于统计的语言模型，其认为在一个句子中某个词出现的概率由前面的词出现的概率决定，一个句子出现的概率是各个词出现的概率的乘积。

对于一个句子，其可以表示为一个word序列：w1, w2, w3, … , wn。我们现在想要计算句子出现的概率，也就是计算P(w1, w2, w3, … , wn)。这个概率我们可以直接用数数的方法求解，但是效果并不好，所以我们利用链式规则，把计算P(w1, w2, w3, … , wn)转化为计算一系列的乘积：P(w1)P(w2|w1)P(w3|w1w2)P(w4|w1w2w3)…P(wn|w1w2…wn-1)。但是转化之后，问题并没有变得简单。于是引入了N-gram。

对于1-gram，其假设是P(wn|w1w2…wn-1)≈P(wn|wn-1)

对于2-gram，其假设是P(wn|w1w2…wn-1)≈P(wn|wn-1,wn-2)

对于3-gram，其假设是P(wn|w1w2…wn-1)≈P(wn|wn-1,wn-2,wn-3)

依次类推。

所以：

在1-gram模型下：

P(w1, w2, w3, … , wn)=P(w1)P(w2|w1)P(w3|w1w2)P(w4|w1w2w3)…P(wn|w1w2…wn-1)

≈P(w1)P(w2|w1)P(w3|w2)P(w4|w3)…P(wn|wn-1)

在2-gram模型下：

P(w1, w2, w3, … , wn)=P(w1)P(w2|w1)P(w3|w1w2)P(w4|w1w2w3)…P(wn|w1w2…wn-1)

≈P(w1)P(w2|w1)P(w3|w1w2)P(w4|w2w3)…P(wn|wn-2wn-1)

在3-gram模型下：

P(w1, w2, w3, … , wn)=P(w1)P(w2|w1)P(w3|w1w2)P(w4|w1w2w3)…P(wn|w1w2…wn-1)

≈P(w1)P(w2|w1)P(w3|w1w2)P(w4|w1w2w3)…P(wn|wn-3wn-2wn-1)



<br>
<br>
<br>
<br>

## Reference:

1.[N-gram语言模型简单介绍](https://www.cnblogs.com/wzm-xu/p/4229819.html)
