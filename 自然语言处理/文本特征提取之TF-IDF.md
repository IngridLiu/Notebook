# 文本特征提取之TF-IDF

<br>
<br>

TF-IDF（term frequency-inverse document frequency），是一种统计方法，用以评估一字词对于一个文件集或一个语料库中的其中一份文件的重要程度。TF-IDF是一种用于信息检索与数据挖掘的常用加权技术。TF意思是（Term Frequency），IDF意思是逆文本频率指数（Inverse Document Frequency）。字词的重要性会随着它在一个文本中出现的次数成正比增加，但同时会随着它在语料库中出现的频率成反比下降。

TF-IDF的主要思想是：如果某个词或者短语在一篇文章中出现的频率TF高，并且在其他文章中很少出现，则认为此词或者短语有很好的区分能力，适合用来分类。TF-IDF实际上是TF*IDF，TF词频（Term Frequency）表示词条在文件d中出现的频率，IDF逆向文件频率（Inverse Document Frequency）。

** 词频（term frequency, TF）** 指的是某一个给定的词语在该文件中出现的频率。这个数字是对词数（term count）的归一化，以防止它偏向长的文件（同一个词语在长文件里可能会比短文件有更高的词数，而不管该词语重要与否。）。对于在某一特定文件里的词语来说，它的重要性可表示为：

![](https://gss1.bdstatic.com/9vo3dSag_xI4khGkpoWK1HF6hhy/baike/s%3D220/sign=c690d729abec8a13101a50e2c7019157/5ab5c9ea15ce36d3448570f638f33a87e850b177.jpg)

以上式子中分子是该词在文件中的出现次数，而分母则是在文件中所有字词的出现次数之和。

** 逆向文件频率（inverse document frequency，IDF）** 是一个词语普遍重要性的度量。某一特定词语的IDF，可以由总文件数目除以包含该词语之文件的数目，再将得到的商取以10为底的对数得到：

![](http://cdn00.baidu-img.cn/timg?wapbaike&quality=80&size=b196_48&sec=1349839550&di=00ea00797dd8056a3f9876fb13506b79&src=http://imgsrc.baidu.com/baike/pic/item/a8014c086e061d9552eec4fe79f40ad163d9ca48.jpg)

其中：

|D|：语料库中的文件总数

：包含词语的文件数目（即的文件数目）如果该词语不在语料库中，就会导致分母为零，因此一般情况下使用第二个式子作为分母。

然后再计算TF与IDF的乘积。

某一特定文件内的高词语频率，以及该词语在整个文件集合中的低文件频率，可以产生出高权重的TF-IDF。因此，TF-IDF倾向于过滤掉常见的词语，保留重要的词语。

