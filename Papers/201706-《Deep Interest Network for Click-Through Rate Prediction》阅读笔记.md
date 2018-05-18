#《Deep Interest Network for Click-Through Rate Prediction》阅读笔记
<br>
<br>


## 1 （Motivation）Introduction
&emsp;&emsp;在以每次点击成本（cost-per-click，CPC）衡量的广告系统中，广告根据每千米有效成本（effective cost per mille，eCPM）进行排序。每千米有效成本（effective cost per mille，eCPM）由竞价（bid price）和点击率（click-through rate，CTR）表示而成，点击率（click-through rate，CTR）由系统生成。点击率（click-through rate，CTR）的预测对于广告系统具有至关重要的意义。

&emsp;&emsp;受到深度学习在计算机视觉和自然语言领域应用广泛且成效优异的启发，很多基于深度学习的点击率预测模型被提出。这些基于Embedding&MLP的模型一般思路是将原始的高维稀疏特征映射到一个低维空间中，也即对原始特征做了embedding操作，之后将这些特征分组变换为定长向量，最后将它们合并到一起，通过一个全连接网络学习到特征间的交互信息和最终与CTR之间的非线性关系。

&emsp;&emsp;受到Embedding&MLP仅能使用有限的向量长度来表示用户特征的限制，无法表示出用户的兴趣多样性。而用户的兴趣是多种多样的，若要增强向量对用户兴趣多样性的表达能力，需要大量扩大向量维度，而这会引起模型规模增大，易发生过拟合以及计算资源不足的问题。另一方面，用户的行为仅会受到其部分兴趣的影响，例如用户是否会购买护目镜取决于用户上周购买了泳衣而并非鞋子。

&emsp;&emsp;因此，作者提出了一个新的模型，深度兴趣网络（DIN），它通过考虑用户对候选广告的历史行为数据来适应性地计算用户兴趣的表示向量。通过引入本地激活单元，DIN关注（Attention）用户的相关兴趣，这些兴趣通过软搜索用户历史行为的相关部分来获取。并使用加权池化（weighted sum pooling）来获取用户对候选广告的兴趣表示。这增强了模型在有限维度下的表达能力，并且使DIN能够更好的获取用户兴趣的多样性。

&emsp;&emsp;同时针对大规模数据的稀疏问题，作者提出了小批次数据感知正则化（mini-batch aware regularization），mini-batch中只有非零特征的参数参与L2-norm的计算，使得这样的计算规模是可以接受的。此外，作者还设计了数据适应性激活函数（a data adaptive activation function），该函数推广了PReLU，能够适应性的修正输入点的贡献值，实验证明，该激活函数对于训练稀疏特征有所帮助。

<br>
<br>

## 2 Deep Interest Network 模型

### 2.1 特征表示
&emsp;&emsp;在CTR预测问题中，数据通常以多组（mutil-group）分类的形式表示，例如\[weekday=Friday, gender=Female,visited_cate_ids={Bag,Book}, ad_cate_id=Book\]。这类数据通常通过编码的方式转换为高维稀疏二元值。在数学上表示为：第i个特征组被编码为编码向量<img src="http://latex.codecogs.com/gif.latex?\inline&space;t_i\in&space;R^{K_i}" title="t_i\in R^{K_i}" />,其中<img src="http://latex.codecogs.com/gif.latex?\inline&space;K_i" title="K_i" />表示第i个特征组的维度，意味着该特征组有<img src="http://latex.codecogs.com/gif.latex?\inline&space;K_i" title="K_i" />个互不相同的值。<img src="http://latex.codecogs.com/gif.latex?\inline&space;t_i[j]" title="t_i[j]" />是<img src="http://latex.codecogs.com/gif.latex?\inline&space;t_i" title="t_i" />特征组的第j个元素，其中<img src="http://latex.codecogs.com/gif.latex?\inline&space;t_i[j]\in&space;\{0,1\}" title="t_i[j]\in \{0,1\}" />。<img src="http://latex.codecogs.com/gif.latex?\inline&space;\sum_{j=1}^{K_i}t_i[j]=k" title="\sum_{j=1}^{K_i}t_i[j]=k" />，使用one-hot编码时k=1，使用mutil-hot编码时k>1。则，一条数据可以基于特征组表示为<img src="http://latex.codecogs.com/gif.latex?\inline&space;x=[t_1^T,t_2^T,...,t_M^T]^T" title="x=[t_1^T,t_2^T,...,t_M^T]^T" />，其中M表示特征组的个数，<img src="http://latex.codecogs.com/gif.latex?\inline&space;\sum_{i=1}^M{K_i}=K" title="\sum_{i=1}^M{K_i}=K" />,K表示整个特征空间的维度。

&emsp;&emsp;？？？此处不太懂mutil-hot怎么编码

&emsp;&emsp;将数据特征分为四类，再将每一类分为特征组（Feature Group），特征表示可以见下表1：

<div align="center">
    <img src="https://upload-images.jianshu.io/upload_images/10947003-4e63056f69a80f98.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/800"><图1：特征表示/img>
</div>
&emsp;&emsp;则四个类别中的特征可以表示如下图所示：
<div>
    <img src="https://upload-images.jianshu.io/upload_images/10947003-ca226c974b791ff6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/800">图2：特征表示示例</img>
</div>


### 2.2 基础模型（Base Model，Embedding&MLP）
&emsp;&emsp;本文中的模型基于Embedding&MLP的结构，如下图3所示：
<div align="center">
    <img src="https://upload-images.jianshu.io/upload_images/10947003-2ff62a582e2d9462.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/800"></img>
    <p>图3：基本模型</p>
</div>

&emsp;&emsp;该结构由多个部分构成。

#### 2.2.1 嵌入层（Embedding Layer）
&emsp;&emsp;由于输入都是高维稀疏二元向量，需使用嵌入层将其转换为低维密集向量。对于第i个特征向量组，用<img src="http://latex.codecogs.com/gif.latex?\inline&space;W^i=[w_1^i,...,w_j^i,...,w_{K_i}^i]\in&space;R^{D\times&space;K}" title="W^i=[w_1^i,...,w_j^i,...,w_{K_i}^i]\in R^{D\times K}" />表示第i个嵌入字典，其中<img src="http://latex.codecogs.com/gif.latex?\inline&space;w_j^i\in&space;R^D" title="w_j^i\in R^D" />是一个维度为D的嵌入式向量。嵌入向量的计算过程如下：

&emsp;&emsp; - 若<img src="http://latex.codecogs.com/gif.latex?\inline&space;t_i" title="t_i" />是one-hot向量，其中第j个元素<img src="http://latex.codecogs.com/gif.latex?\inline&space;t_i[j]=1" title="t_i[j]=1" />，则<img src="http://latex.codecogs.com/gif.latex?\inline&space;t_i" title="t_i" />的嵌入式表示为一个single embedding vector<img src="http://latex.codecogs.com/gif.latex?\inline&space;e_i=w_j^i" title="e_i=w_j^i" />。

&emsp;&emsp; - 若<img src="http://latex.codecogs.com/gif.latex?\inline&space;t_i" title="t_i" />是nutil-hot向量，其中<img src="http://latex.codecogs.com/gif.latex?\inline&space;t_i[j]=1" title="t_i[j]=1" />for <img src="http://latex.codecogs.com/gif.latex?\inline&space;j\in&space;\{i_1,i_2,...,i_k\}" title="j\in \{i_1,i_2,...,i_k\}" />,则<img src="http://latex.codecogs.com/gif.latex?\inline&space;t_i" title="t_i" />的嵌入向量表示为<img src="http://latex.codecogs.com/gif.latex?\inline&space;{e_{i_1},e_{i_2},...,e_{i_k}}={w_{i_1}^i,w_{i_2}^i,...,w_{i_k}^i}" title="{e_{i_1},e_{i_2},...,e_{i_k}}={w_{i_1}^i,w_{i_2}^i,...,w_{i_k}^i}" />。

#### 2.2.2 Pooling层和Concat层
&emsp;&emsp;在本文中仅有用户行为特征采取mutil-hot编码，而不同的用户会有不同数量的行为数据。因此，对于不同的用户来说，mutil-hot向量中非零数的数目是不一样的。由于全连接层智能处理定长的数据，所以需要对embedding层做一个池化，得到一个定长的向量，如公式（1）：

<div align="center">
    <img src="http://latex.codecogs.com/gif.latex?\inline&space;e_i&space;=&space;pooling(e_{i_1},e_{i_2},...,e{i_k})" title="e_i = pooling(e_{i_1},e_{i_2},...,e{i_k})" />&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;公式（1）
</div>

&emsp;&emsp;较常用的pooling层为sum pooling和average pooling，pooling层对嵌入式向量的每一个元素进行sum或者average操作（apply element-wise sum/average operations to the list of embedding vectors）。

&emsp;&emsp;concat层将所有的向量合并起来表示全部的特征。

&emsp;&emsp;此处pooling层操作针对用户行为特征，concat层针对每一组特征以及总的所有特征。

#### 2.2.3 MLP
&emsp;&emsp;全连接层将自动学习concat之后的特征表示的特征。

#### 2.2.4 Loss
&emsp;&emsp;基础模型中所用的目标函数（objective function）/损失函数（loss function）为negative log-likelihood function，表示为公式（2）：
<div align="center">
    <img src="http://latex.codecogs.com/gif.latex?L=-\frac{1}{N}\sum_{(x,y)\in&space;S}(ylogp(x)&plus;(1-y)log(1-p(x)))" title="L=-\frac{1}{N}\sum_{(x,y)\in S}(ylogp(x)+(1-y)log(1-p(x)))" />&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;公式（2）
</div>
&emsp;&emsp;其中S表示大小为N的训练集S，x表示模型输入，<img src="http://latex.codecogs.com/gif.latex?\inline&space;y\in&space;\{0,1\}" title="y\in \{0,1\}" />表示标签，p(x)是经过softmax层之后的输出，表示x会被点击的概率。

### 2.3 Deep Interest Network结构
&emsp;&emsp;Deep Interest Network的结构如下图4所示。

![图4：Deep Interest Network结构](https://upload-images.jianshu.io/upload_images/10947003-a4423b7681ec1e24.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/800)

&emsp;&emsp;与基础模型相比较，DIN引入了新的local activation unit，保持了模型的总体结构。具体来说，activation units主要应用于用户的行为特征，主要是为了计算用户对候选广告A的表达（representation），记为<img src="http://latex.codecogs.com/gif.latex?\inline&space;\upsilon&space;_U" title="\upsilon _U" />,如公式（3）所示：
<div align="center">
    <img src="http://latex.codecogs.com/gif.latex?\upsilon&space;_U(A)=f(\upsilon_A,e_1,e_2,...,e_H)=\sum_{j=1}^Ha(e_j,\upsilon_A)e_j=\sum_{j=1}^Hw_je_j" title="\upsilon _U(A)=f(\upsilon_A,e_1,e_2,...,e_H)=\sum_{j=1}^Ha(e_j,\upsilon_A)e_j=\sum_{j=1}^Hw_je_j" />
</div>

&emsp;&emsp;其中<img src="http://latex.codecogs.com/gif.latex?\inline&space;\{e_1,e_2,...,e_H\}" title="\{e_1,e_2,...,e_H\}" />为用户U的长度为H的行为的嵌入式向量列表，<img src="http://latex.codecogs.com/gif.latex?\inline&space;\upsilon&space;_A" title="\upsilon _A" />为广告A的嵌入式向量。<img src="http://latex.codecogs.com/gif.latex?\inline&space;\upsilon&space;_U(A)" title="\upsilon _U(A)" />随着广告的不同而不同。<img src="http://latex.codecogs.com/gif.latex?\inline&space;a(&space;\cdot&space;)" title="a( \cdot )" />是一个将输出作为激活权重的前馈网络，从图4中可以看出。除了两个嵌入式向量，<img src="http://latex.codecogs.com/gif.latex?\inline&space;a(&space;\cdot&space;)" title="a( \cdot )" />还将它们的结果传入下一层网络，从而帮助相关性的建模。

&emsp;&emsp;本地激活单元（load activation unit)与attention机制有相似的思想，主要是为了改变用户兴趣的强度。与传统的attention机制不同的是取消了对<img src="http://latex.codecogs.com/gif.latex?\inline&space;a(\cdot&space;)" title="a(\cdot )" />的输出的正则化（normalization）。

<br>
<br>

## 3 模型训练策略

### 3.1 小批量感知正则化（Mini-batch Aware Regularization）
&emsp;&emsp;在模型训练中，overfitting是一个很严重的问题，一般通过引入惩罚项来解决。通过实验作者发现，训练小批量数据集时loss下降明显，但是常用的l1、l2 norm作用不大，于是作者提出了mini-batch aware regularizer。在小批量感知的正则化中，只计算稀疏特征参数的l2 norm。

&emsp;&emsp;我们用<img src="http://latex.codecogs.com/gif.latex?\inline&space;W\in&space;R^{D\times&space;K}" title="W\in R^{D\times K}" />表示整个嵌入式词典的参数，其中D表示嵌入式向量的维度，K表示特征向量的维度。我们可以在W上将l2 norm扩张为公式4：

<div align="center">
    <img src="http://latex.codecogs.com/gif.latex?L_2(W)={||W||}_2^2=\sum_{j=1}^K=\sum_{(x,y)\in&space;S}\sum_{j=1}^K\frac{I(x_j\neq&space;0)}{n_j}{||w_j||_2^2}" title="L_2(W)={||W||}_2^2=\sum_{j=1}^K=\sum_{(x,y)\in S}\sum_{j=1}^K\frac{I(x_j\neq 0)}{n_j}{||w_j||_2^2}" />&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;(公式4）
</div>

&emsp;&emsp;其中<img src="http://latex.codecogs.com/gif.latex?\inline&space;w_j\in&space;R^D" title="w_j\in R^D" />为第j个嵌入式向量，<img src="http://latex.codecogs.com/gif.latex?\inline&space;I(x_j\neq&space;0)" title="I(x_j\neq 0)" />标记了实例x是否含有第j个特征，<img src="http://latex.codecogs.com/gif.latex?\inline&space;n_j" title="n_j" />是第j个特征在所有数据集中出现的频数。可以将公式4以小批量感知的方式转换为公式5：

<div align="center">
    <img src="http://latex.codecogs.com/gif.latex?L_2(W)=\sum_{j=1}^K\sum_{m=1}^B\sum_{(x,y)\in&space;B_m}\frac{I(x_j\neq&space;0)}{n_j}{||w_j||}_2^2" title="L_2(W)=\sum_{j=1}^K\sum_{m=1}^B\sum_{(x,y)\in B_m}\frac{I(x_j\neq 0)}{n_j}{||w_j||}_2^2" />&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;（公式5）
</div>

&emsp;&emsp;其中B表示mini-batch的数量，<img src="http://latex.codecogs.com/gif.latex?\inline&space;B_m" title="B_m" />表示第m个mini-batch。使<img src="http://latex.codecogs.com/gif.latex?\inline&space;\alpha_{mj}=max(x,y)\in&space;B_mI(x_j\neq&space;0)" title="\alpha_{mj}=max(x,y)\in B_mI(x_j\neq 0)" />表示，若第m个mini-batch<img src="http://latex.codecogs.com/gif.latex?\inline&space;B_m" title="B_m" />中至少有一个实例有特征j，则可以将公式5近似为公式6：

<div>
    <img src="http://latex.codecogs.com/gif.latex?L_2(W)\approx&space;\sum_{j=1}^K\sum_{m=1}^B\frac{\alpha_{mj}}{n_j}&space;{||w_j||_2^2}" title="L_2(W)\approx \sum_{j=1}^K\sum_{m=1}^B\frac{\alpha_{mj}}{n_j} {||w_j||_2^2}" />&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;（公式6）
</div align="center">

&emsp;&emsp;这样，就得到了mini-batch感知的l2近似正则化。对于第m个mini-batch，嵌入式向量w的第j个特征的更新如公式7所示（基于梯度下降）：

<div align="center">
    <img src="http://latex.codecogs.com/gif.latex?w_j\leftarrow&space;w_j-\eta&space;\left&space;[&space;\frac{1}{|B_m|}\sum_{(x,y)\in&space;B_m}\frac{\partial&space;L(p(x),y)}{\partial{w_j}}&space;&plus;\lambda&space;\frac{\alpha&space;_{mj}}{n_j}w_j\right&space;]" title="w_j\leftarrow w_j-\eta \left [ \frac{1}{|B_m|}\sum_{(x,y)\in B_m}\frac{\partial L(p(x),y)}{\partial{w_j}} +\lambda \frac{\alpha _{mj}}{n_j}w_j\right ]" />&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;（公式7）    
</div>


### 3.2 数据适应性的激活函数(Data Adaptive Activation Function)
&emsp;&emsp;PReLU是常用的激活函数，如公式8所示：

<div align="center">
    <img src="http://latex.codecogs.com/gif.latex?f(s)=\left\{\begin{matrix}&space;s&space;&&space;if&space;\;&space;s>0\\&space;\alpha&space;s&&space;if&space;\;&space;s\leqslant&space;0&space;\end{matrix}\right.&space;=p(s)\cdot&space;s&plus;(1-p(s))\cdot&space;\alpha&space;s" title="f(s)=\left\{\begin{matrix} s & if \; s>0\\ \alpha s& if \; s\leqslant 0 \end{matrix}\right. =p(s)\cdot s+(1-p(s))\cdot \alpha s" />&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;(公式8)    
</div>

&emsp;&emsp;其中s是激活函数f(·)的一维输入，<img src="http://latex.codecogs.com/gif.latex?\inline&space;p(s)=I(s>0)" title="p(s)=I(s>0)" />控制着选择<img src="http://latex.codecogs.com/gif.latex?\inline&space;f(s)=s" title="f(s)=s" />还是<img src="http://latex.codecogs.com/gif.latex?\inline&space;f(s)=\alpha&space;s" title="f(s)=\alpha s" />，<img src="http://latex.codecogs.com/gif.latex?\inline&space;\alpha" title="\alpha" />为需要学习的参数。将<img src="http://latex.codecogs.com/gif.latex?\inline&space;p(s)" title="p(s)" />称为控制函数。下图5的左侧表示了PReLU的形式：

<div align="center">
    <img src="https://upload-images.jianshu.io/upload_images/10947003-e0f20f9bffb3406e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/400">图5：PReLU和Dice的控制函数</img>
</div>

&emsp;&emsp;PReLU的0点无法调节，当每层的输入有不同的分布时不适用。作者提出了新的适应性激活函数（Adaptive activiation function ）Dice：

<div align="center">
    <img src="http://latex.codecogs.com/gif.latex?\dpi{150}&space;f(s)=p(s)\cdot&space;&plus;(1-p(s))\cdot\alpha&space;s,\;\;p(s)&space;=&space;\frac{1}{1&plus;e^{-\frac{s-E[s]}{\sqrt{Var[s]&plus;\varepsilon&space;}}}}" title="f(s)=p(s)\cdot +(1-p(s))\cdot\alpha s,\;\;p(s) = \frac{1}{1+e^{-\frac{s-E[s]}{\sqrt{Var[s]+\varepsilon }}}}" />&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;（公式9）
</div>

&emsp;&emsp;该公式使得激活函数的变换如图5右侧所示。其中<img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{100}&space;E[s]" title="E[s]" />和<img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{100}&space;Var[s]" title="Var[s]" />分别为每一个mini-batch中的输入数据的均值（mean）和方差（variance），<img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{100}&space;\varepsilon" title="\varepsilon" />是提前设定的超参数，在本文使得实验中设为<img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{100}&space;10^{-8}" title="10^{-8}" />。

&emsp;&emsp;能够将Dice设为PReLU的推广。当<img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{100}&space;E[s]=0" title="E[s]=0" />及<img src="http://latex.codecogs.com/gif.latex?\inline&space;\dpi{100}&space;Var[s]=0" title="Var[s]=0" /> 时，PReLU=Dice。

<br>
<br>

## 4 实验
### 4.1 实验数据和设置（Datasets and Experimental Setup）
&emsp;&emsp;[Amazon Dataset](http://jmcauley.ucsd.edu/data/amazon/)

&emsp;&emsp;[MovieLens Dataset](https://grouplens.org/datasets/movielens/20m/)


<br>
<br>
<br>

## Reference：
1. [论文代码](https://github.com/zhougr1993/DeepInterestNetwork)
2. [《Deep Interest Network for Click-Through Rate Prediction》阅读笔记](https://zhuanlan.zhihu.com/p/30597671)