# 词向量模型-fastText

<br>
<br>

fastText在使用负采样的skip-gram模型的基础上，将每个中心词视为子词（subword）的集合，并学习子词的词向量。

以where这个词为例，设子词为3个字符，它的子词包括<"wh"、"whe"、"her"、"ere"、"re">和特殊子词（整词）"<where>"。其中的"<"和">"是为了将作为前后缀的子词区分出来。而且，这里的子词"her"与整词"<her>"也可被区分。



<br>
<br>
<br>
<br>

## Reference:

1. [动手学深度学习第十七课：GloVe、fastText和使用预训练的词向量](https://www.youtube.com/watch?v=ioSnNLZSQq0)

