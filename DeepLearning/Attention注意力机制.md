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

### 1.3 例子
&emsp;&emsp;比如输入<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;X" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;X" title="X" /></a>是"Tom chase Jerry"，模型翻译出"汤姆 追逐 杰瑞"。在翻译"杰瑞"的时候，"Jerry"对"杰瑞"的贡献更重要。但是显然普通的Encoder-Decoder模型中，三个单词对于翻译"Jerry-杰瑞"的贡献是一样的。

&emsp;&emsp;解决方案应该是，每个单词对于翻译"杰瑞"的贡献应该不一样，如翻译"杰瑞"时：

<div align="center">
    <a href="http://www.codecogs.com/eqnedit.php?latex=\dpi{150}&space;(Tom,&space;0.3),&space;\;&space;(Chase,&space;0.2),&space;\;&space;(Jerry,&space;0.5)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\dpi{150}&space;(Tom,&space;0.3),&space;\;&space;(Chase,&space;0.2),&space;\;&space;(Jerry,&space;0.5)" title="(Tom, 0.3), \; (Chase, 0.2), \; (Jerry, 0.5)" /></a>
</div>

<br>

## 2 Attention Model
### 2.1 基本架构
&emsp;&emsp;Attention Model的架构如下：

![](https://upload-images.jianshu.io/upload_images/10947003-e12ab1b24b48d066.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/400)

&emsp;&emsp;如图所示，生成每个单词<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;y_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;y_i" title="y_i" /></a>时，都有各自的语义向量<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;C_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;C_i" title="C_i" /></a>，不再是统一的<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;C" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;C" title="C" /></a>。

<div align="center">
    <a href="http://www.codecogs.com/eqnedit.php?latex=\dpi{120}&space;y_i&space;=&space;f(C_i,&space;y_1,&space;\cdots,&space;y_{i-1})" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\dpi{120}&space;y_i&space;=&space;f(C_i,&space;y_1,&space;\cdots,&space;y_{i-1})" title="y_i = f(C_i, y_1, \cdots, y_{i-1})" /></a>
</div align="center">

&emsp;&emsp;例如，前3个单词的生成：

<div>
    <a href="http://www.codecogs.com/eqnedit.php?latex=\dpi{120}&space;&&space;y_1&space;=&space;f(C_1)&space;\\&space;&&space;y_2&space;=&space;f(C_2,&space;y_1)&space;\\&space;&&space;y_3&space;=&space;f(C_3,&space;y_1,&space;y_2)&space;\\" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\dpi{120}&space;&&space;y_1&space;=&space;f(C_1)&space;\\&space;&&space;y_2&space;=&space;f(C_2,&space;y_1)&space;\\&space;&&space;y_3&space;=&space;f(C_3,&space;y_1,&space;y_2)&space;\\" title="& y_1 = f(C_1) \\ & y_2 = f(C_2, y_1) \\ & y_3 = f(C_3, y_1, y_2) \\" /></a>
</div>

### 2.2 语义向量的计算
&emsp;&emsp;注意力分配概率<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;a_{ij}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;a_{ij}" title="a_{ij}" /></a>表示<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;y_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;y_i" title="y_i" /></a>收到<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;x_j" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;x_j" title="x_j" /></a>的注意力概率。

&emsp;&emsp;例如<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;X=(Tom,&space;Chase,&space;Jerry)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;X=(Tom,&space;Chase,&space;Jerry)" title="X=(Tom, Chase, Jerry)" /></a>，Y=(汤姆,追逐,杰瑞)。<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;a_{12}=0.2" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;a_{12}=0.2" title="a_{12}=0.2" /></a>表示汤姆收到来自Chase的注意力概率是0.2。

&emsp;&emsp;有下面的注意力分配矩阵：

<div align="center">
    <a href="http://www.codecogs.com/eqnedit.php?latex=\dpi{120}&space;A&space;=&space;[a_{ij}]&space;=&space;\begin&space;{bmatrix}&space;0.6&space;&&space;0.2&space;&&space;0.2&space;\\&space;0.2&space;&&space;0.7&space;&&space;0.1&space;\\&space;0.3&space;&&space;0.1&space;&&space;0.5&space;\\&space;\end&space;{bmatrix}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\dpi{120}&space;A&space;=&space;[a_{ij}]&space;=&space;\begin&space;{bmatrix}&space;0.6&space;&&space;0.2&space;&&space;0.2&space;\\&space;0.2&space;&&space;0.7&space;&&space;0.1&space;\\&space;0.3&space;&&space;0.1&space;&&space;0.5&space;\\&space;\end&space;{bmatrix}" title="A = [a_{ij}] = \begin {bmatrix} 0.6 & 0.2 & 0.2 \\ 0.2 & 0.7 & 0.1 \\ 0.3 & 0.1 & 0.5 \\ \end {bmatrix}" /></a>
</div>

&emsp;&emsp;第<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;i" title="i" /></a>行表示<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;y_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;y_i" title="y_i" /></a>收到的所有来自输入单词的注意力分配概率。<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;y_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;y_i" title="y_i" /></a>的语义向量<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;C_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;C_i" title="C_i" /></a>由这些注意力分配概率和Encoder对单词x_j的转换函数相乘，计算而成，例如：

<div align="center">
    <a href="http://www.codecogs.com/eqnedit.php?latex=\dpi{120}&space;&&space;C_1&space;=&space;C_{}&space;=&space;g(0.6&space;\cdot&space;h(Tom),\;&space;0.2&space;\cdot&space;h(Chase),\;&space;0.2&space;\cdot&space;h(Jerry))&space;\\&space;&&space;C_2&space;=&space;C_{}&space;=&space;g(0.2&space;\cdot&space;h(Tom)&space;,\;0.7&space;\cdot&space;h(Chase)&space;,\;0.1&space;\cdot&space;h(Jerry))&space;\\&space;&&space;C_3&space;=&space;C_{}&space;=&space;g(0.3&space;\cdot&space;h(Tom),\;&space;0.2&space;\cdot&space;h(Chase)&space;,\;0.5&space;\cdot&space;h(Jerry))&space;\\" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\dpi{120}&space;&&space;C_1&space;=&space;C_{}&space;=&space;g(0.6&space;\cdot&space;h(Tom),\;&space;0.2&space;\cdot&space;h(Chase),\;&space;0.2&space;\cdot&space;h(Jerry))&space;\\&space;&&space;C_2&space;=&space;C_{}&space;=&space;g(0.2&space;\cdot&space;h(Tom)&space;,\;0.7&space;\cdot&space;h(Chase)&space;,\;0.1&space;\cdot&space;h(Jerry))&space;\\&space;&&space;C_3&space;=&space;C_{}&space;=&space;g(0.3&space;\cdot&space;h(Tom),\;&space;0.2&space;\cdot&space;h(Chase)&space;,\;0.5&space;\cdot&space;h(Jerry))&space;\\" title="& C_1 = C_{} = g(0.6 \cdot h(Tom),\; 0.2 \cdot h(Chase),\; 0.2 \cdot h(Jerry)) \\ & C_2 = C_{} = g(0.2 \cdot h(Tom) ,\;0.7 \cdot h(Chase) ,\;0.1 \cdot h(Jerry)) \\ & C_3 = C_{} = g(0.3 \cdot h(Tom),\; 0.2 \cdot h(Chase) ,\;0.5 \cdot h(Jerry)) \\" /></a>
</div>

&emsp;&emsp;<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;h(x_j)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;h(x_j)" title="h(x_j)" /></a>就表示Encoder对输入英文单词的某种变换函数。比如Encoder使用RNN的话，<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;h(x_j)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;h(x_j)" title="h(x_j)" /></a>往往都是某个时刻输入<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;x_j" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;x_j" title="x_j" /></a>后隐藏节点的状态值。

&emsp;&emsp;g函数表示注意力分配后的整个句子的语义转换信息，一般都是加权求和，则有语义向量计算公式：

<div align="center">
    <a href="http://www.codecogs.com/eqnedit.php?latex=\dpi{120}&space;C_i&space;=&space;\sum_{j=1}^{T_x}&space;a_{ij}&space;\cdot&space;h_j,&space;\quad&space;h_j&space;=&space;h(x_j)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\dpi{120}&space;C_i&space;=&space;\sum_{j=1}^{T_x}&space;a_{ij}&space;\cdot&space;h_j,&space;\quad&space;h_j&space;=&space;h(x_j)" title="C_i = \sum_{j=1}^{T_x} a_{ij} \cdot h_j, \quad h_j = h(x_j)" /></a>
</div>

&emsp;&emsp;其中<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;T_x" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;T_x" title="T_x" /></a>代表输入句子的长度。形象来看计算过程如下图：
![](https://upload-images.jianshu.io/upload_images/10947003-399ca05fdb57594d.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/400)


### 2.3 注意力分配概率计算

???

&emsp;&emsp;语义向量需要注意力分配概率和Encoder输入单词变换函数来共同计算得到。但是比如汤姆收到的分配概率<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;a_1&space;=&space;(0.6,&space;0.2,&space;0.2)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;a_1&space;=&space;(0.6,&space;0.2,&space;0.2)" title="a_1 = (0.6, 0.2, 0.2)" /></a>是怎么计算得到的呢？

&emsp;&emsp;这里采用RNN作为Encoder和Decoder来说明。

![](https://upload-images.jianshu.io/upload_images/10947003-68d60b0cbdf27cbf.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/600)

&emsp;&emsp;注意力分配概率如下图计算：

![](https://upload-images.jianshu.io/upload_images/10947003-9cf88e456e412672.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/600)

&emsp;&emsp;对于<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;a_{ij}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;a_{ij}" title="a_{ij}" /></a>其实是通过一个对齐函数F来进行计算的，两个参数：输入节点<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;j" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;j" title="j" /></a>和输出节点<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;i" title="i" /></a>，当然一般是取隐层状态。

<div align="center">
    <a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;a_i&space;=&space;F(i,&space;j),&space;\quad&space;j&space;\in&space;[1,&space;T_x],&space;\quad&space;h(j)\,Encoder,&space;\;&space;H(i)\,Decoder" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;a_i&space;=&space;F(i,&space;j),&space;\quad&space;j&space;\in&space;[1,&space;T_x],&space;\quad&space;h(j)\,Encoder,&space;\;&space;H(i)\,Decoder" title="a_i = F(i, j), \quad j \in [1, T_x], \quad h(j)\,Encoder, \; H(i)\,Decoder" /></a>
</div>

&emsp;&emsp;<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;\color{blue}{F(i,&space;j)}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;\color{blue}{F(i,&space;j)}" title="\color{blue}{F(i, j)}" /></a>代表<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;y_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;y_i" title="y_i" /></a>和<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;x_j" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;x_j" title="x_j" /></a>的对齐可能性。一般F输出后，再经过softmax就得到了注意力分配概率。

### 2.4 AM模型的意义

&emsp;&emsp;一般地，会把AM模型看成单词对齐模型，输入句子单词和这个目标生成句子单词的对齐概率。

&emsp;&emsp;其实，理解为影响力模型也是合理的。就是在生成目标单词的时候，输入句子中的每个单词，对于生成当前目标单词有多大的影响程度。

&emsp;&emsp;AM模型有很多的应用，思想大都如此。

### 2.5 文本摘要例子

&emsp;&emsp;比如文本摘要的例子，输入一个长句，提取出重要的信息。

&emsp;&emsp;输入"russian defense minister ivanov called sunday for the creation of a joint front for combating global terrorism"。

&emsp;&emsp;输出"russia calls for joint front against terrorism"。

&emsp;&emsp;下图代表着输入单词对输出单词的影响力，颜色越深，影响力越大，注意力分配概率也越大。

![](https://upload-images.jianshu.io/upload_images/10947003-8c1005231ca464da.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


<br>

## 3 PyTorch翻译AM实现

### 3.1 思想

&emsp;&emsp;参考[《Neural Machine Translation by Jointly Learning to Align and Translate》](https://arxiv.org/abs/1409.0473)

&emsp;&emsp;生成目标单词<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;y_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;y_i" title="y_i" /></a>的计算概率是：

<div align="center">
    <a href="http://www.codecogs.com/eqnedit.php?latex=\dpi{120}&space;p(y_i&space;\mid&space;(y_1,\cdots,&space;y_{i-1}),&space;x)&space;=&space;g(y_{i-1},&space;s_i,&space;c_i)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\dpi{120}&space;p(y_i&space;\mid&space;(y_1,\cdots,&space;y_{i-1}),&space;x)&space;=&space;g(y_{i-1},&space;s_i,&space;c_i)" title="p(y_i \mid (y_1,\cdots, y_{i-1}), x) = g(y_{i-1}, s_i, c_i)" /></a>
</div>

&emsp;&emsp;符号意义说明：

&emsp;&emsp;<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;y_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;y_i" title="y_i" /></a>：当前应该生成的目标单词，<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;y_{i-1}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;y_{i-1}" title="y_{i-1}" /></a>上一个节点的输出单词。

&emsp;&emsp;<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;s_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;s_i" title="s_i" /></a>：当前节点的隐藏状态

&emsp;&emsp;<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;c_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;c_i" title="c_i" /></a>：生成当前单词应该有的语义向量

&emsp;&emsp;<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;g" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;g" title="g" /></a>：全连接层的函数

- **隐层状态<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;s_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;s_i" title="s_i" /></a>**

&emsp;&emsp;求当前Decoder隐层状态<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;s_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;s_i" title="s_i" /></a>；由上一层的隐状态<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;s_{i-1}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;s_{i-1}" title="s_{i-1}" /></a>，输出单词<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;y_{i-1}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;y_{i-1}" title="y_{i-1}" /></a>，语义向量<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;c_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;c_i" title="c_i" /></a>决定。

<div align="center">
    <a href="http://www.codecogs.com/eqnedit.php?latex=\dpi{120}&space;s_i&space;=&space;f(s_{i-1},&space;y_{i-1},&space;c_i)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\dpi{120}&space;s_i&space;=&space;f(s_{i-1},&space;y_{i-1},&space;c_i)" title="s_i = f(s_{i-1}, y_{i-1}, c_i)" /></a>
</div>

- **语义向量<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;c_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;c_i" title="c_i" /></a>**

&emsp;&emsp;语义向量：分配权值<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;\dpi{120}&space;a_{ij}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{120}&space;a_{ij}" title="a_{ij}" /></a>,Encoder的输出：

<div align="center">
    <a href="http://www.codecogs.com/eqnedit.php?latex=\dpi{120}&space;c_i&space;=&space;\sum_{j=1}^{T_x}&space;a_{ij}&space;\cdot&space;h_j,&space;\quad&space;h_j&space;=&space;h(x_j)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\dpi{120}&space;c_i&space;=&space;\sum_{j=1}^{T_x}&space;a_{ij}&space;\cdot&space;h_j,&space;\quad&space;h_j&space;=&space;h(x_j)" title="c_i = \sum_{j=1}^{T_x} a_{ij} \cdot h_j, \quad h_j = h(x_j)" /></a>
</div>

- **分配概率<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;a_{ij}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;a_{ij}" title="a_{ij}" /></a>**

&emsp;&emsp;注意力分配概率<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;a_{ij}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;a_{ij}" title="a_{ij}" /></a>，<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;y_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;y_i" title="y_i" /></a>收到<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;x_j" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;x_j" title="x_j" /></a>的注意力：分配能量<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;e_{ij}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;e_{ij}" title="e_{ij}" /></a>

<div align="center">
    <a href="http://www.codecogs.com/eqnedit.php?latex=a_{ij}&space;=&space;\frac{\exp(e_{ij})}&space;{\sum_{k=1}^{T_x}&space;\exp&space;(e_{ik})}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?a_{ij}&space;=&space;\frac{\exp(e_{ij})}&space;{\sum_{k=1}^{T_x}&space;\exp&space;(e_{ik})}" title="a_{ij} = \frac{\exp(e_{ij})} {\sum_{k=1}^{T_x} \exp (e_{ik})}" /></a>
</div>

- **分配能量<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;e_{ij}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;e_{ij}" title="e_{ij}" /></a>**

&emsp;&emsp;<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;x_j" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;x_j" title="x_j" /></a>分配给<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;y_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;y_i" title="y_i" /></a>的能量，由encoder的隐状态<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;h_j" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;h_j" title="h_j" /></a>和decoder的上一层的隐状态<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;s_{i-1}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;s_{i-1}" title="s_{i-1}" /></a>计算而成。a函数就是一个线性层。也就是上面的F函数。

<div align="center">
    <a href="http://www.codecogs.com/eqnedit.php?latex=e_{ij}&space;=&space;a(s_{i-1},&space;h_j)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?e_{ij}&space;=&space;a(s_{i-1},&space;h_j)" title="e_{ij} = a(s_{i-1}, h_j)" /></a>
</div>

### 3.2 PyTorch实现

&emsp;&emsp;Decoder由4层组成
&emsp;&emsp;- embedding : word2vec
&emsp;&emsp;- attention layer: 为每个encoder的output计算Attention
&emsp;&emsp;- RNN layer:
&emsp;&emsp;- output layer:
&emsp;&emsp;Decoder输入<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;s_{i-1}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;s_{i-1}" title="s_{i-1}" /></a>,<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;y_{i-1}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;y_{i-1}" title="y_{i-1}" /></a>和encoder的所有outputs<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;h_*" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;h_*" title="h_*" /></a>。 

**Embedding Layer**
&emsp;&emsp;输入<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;y_{i-1}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;y_{i-1}" title="y_{i-1}" /></a>，对齐进行编码
```
# y(i-1)
embedded = embedding(last_rnn_output)
```

**Attention Layer**
&emsp;&emsp;输入<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;s_{i-1}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;s_{i-1}" title="s_{i-1}" /></a>，<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;h_j" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;h_j" title="h_j" /></a>，输出分配能量<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;e_{ij}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;e_{ij}" title="e_{ij}" /></a>，计算出<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;a_{ij}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;a_{ij}" title="a_{ij}" /></a>。
```
attn_weights[j] = attn_layer(last_hidden, encoder_outputs[j])
attn_weights = normalize(attn_weights)
```

**计算语义向量**
&emsp;&emsp;求语义向量<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;c_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;c_i" title="c_i" /></a>，一般是加权求和。
```
context = sum(attn_weights * encoder_outputs)
```

**RNN Layer**
&emsp;&emsp;输入<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;s_{i-1}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;s_{i-1}" title="s_{i-1}" /></a>，<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;y_{i-1}" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;y_{i-1}" title="y_{i-1}" /></a>，<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;c_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;c_i" title="c_i" /></a>，输出<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;y_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;y_i" title="y_i" /></a>。
```
output = out(embedded, rnn_output, context)
```
&emsp;&emsp;


<br>

## 4 相关论文

### 4.1 《Sequence to Sequence Learning with Neural Networks》
### 4.2 《Effective Approaches to Attention-based Neural Machine Translation》
### 4.3 《Neural Machine Translation by Jointly Learning to Align and Translate》
### 4.4 《Attention Is All You Need》



<br>
<br>
<br>
## Reference:
[图文介绍注意力机制](https://plmsmile.github.io/2017/10/10/attention-model/)
[Attention模型方法综述 | 多篇经典论文解读](https://mp.weixin.qq.com/s/sAYOXEjAdA91x3nliHNX8w)