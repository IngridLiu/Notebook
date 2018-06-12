# Attention注意力机制

<br>
<br>

## 1 Encoder-Decoder

### 1.1 基本介绍
&emsp;&emsp;举个翻译的例子，原始句子<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;X&space;=&space;(x_1,&space;x_2,&space;\cdots,&space;x_m)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;X&space;=&space;(x_1,&space;x_2,&space;\cdots,&space;x_m)" title="X = (x_1, x_2, \cdots, x_m)" /></a>，翻译成目标句子<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;Y&space;=&space;(y_1,&space;y_2,&space;\cdots,&space;y_n)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;Y&space;=&space;(y_1,&space;y_2,&space;\cdots,&space;y_n)" title="Y = (y_1, y_2, \cdots, y_n)" /></a>。

&emsp;&emsp;现在采用Encoder-Decoder架构模型，如下图：

![01-encoder-decoder-n.jpg](https://upload-images.jianshu.io/upload_images/10947003-73ec9b7784f5a2cc.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/400)

&emsp;&emsp;Encoder会利用整个原始句子生成一个语义向量，Decoder再利用这个向量翻译成其它语言的句子。这样可以把握整个句子的意思、语法结构、性别信息等等。

&emsp;&emsp;Encoder对<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;X" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;X" title="X" /></a>进行非线性变换得到中间语义向量c:

<div align = "center">
    <a href="http://www.codecogs.com/eqnedit.php?latex=c&space;=&space;G(x_1,&space;x_2,&space;\cdots,&space;x_n)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?c&space;=&space;G(x_1,&space;x_2,&space;\cdots,&space;x_n)" title="c = G(x_1, x_2, \cdots, x_n)" /></a>
</div>

&emsp;&emsp;Decoder根据语义c和生成的历史单词<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;(y_1,&space;y_2,&space;\cdots,&space;y_{i-1})" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;(y_1,&space;y_2,&space;\cdots,&space;y_{i-1})" title="(y_1, y_2, \cdots, y_{i-1})" /></a>来生成第<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;i" title="i" /></a>个单词<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;y_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;y_i" title="y_i" /></a>:

<div align = "center">    
    <a href="http://www.codecogs.com/eqnedit.php?latex=y_i&space;=&space;f(c,&space;y_1,&space;y_2,&space;\cdots,&space;y_{i-1})" target="_blank"><img src="http://latex.codecogs.com/gif.latex?y_i&space;=&space;f(c,&space;y_1,&space;y_2,&space;\cdots,&space;y_{i-1})" title="y_i = f(c, y_1, y_2, \cdots, y_{i-1})" /></a>
</div>

&emsp;&emsp;Encoder-Decoder是个创新大杀器，是个通用的计算框架。Encoder和Decoder具体使用什么模型，都可以自己选择。通常有CNN，RNN，BiRNN，GRU，LSTM，Deep LSTM。上面的内容任意组合，只要得到的效果好，就是一个创新。

### 1.2 缺点
&emsp;&emsp;在生成目标句子<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;Y" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;Y" title="Y" /></a>的单词时，所有的单词<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;y_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;y_i" title="y_i" /></a>使用的语义编码<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;c" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;c" title="c" /></a>都是一样的。而语义编码<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;c" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;c" title="c" /></a>是由句子<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;X" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;X" title="X" /></a>的每个单词经过Encoder编码产生，也就是说每个<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;x_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;x_i" title="x_i" /></a>对所有<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;y_j" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;y_j" title="y_j" /></a>的影响力都是相同的，没有任何区别。所以上面的是注意力不集中的分心模型。
&emsp;&emsp;句子较短时问题不大，但是较长时，所有语义完全通过一个中间语义向量来表示，单词自身的信息已经消失，会丢失更多的细节信息。