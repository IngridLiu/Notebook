#《Deep Interest Network for Click-Through Rate Prediction》阅读笔记

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
    ![图1：特征表示](https://upload-images.jianshu.io/upload_images/10947003-4e63056f69a80f98.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/800)
</div>
&emsp;&emsp;则四个类别中的特征可以表示如下图所示：
<div>
   ![图2：特征表示示例](https://upload-images.jianshu.io/upload_images/10947003-ca226c974b791ff6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1600)
</div>


### 2.2 基础模型（Base Model，Embedding&MLP）
&emsp;&emsp;本文中的模型基于Embedding&MLP的结构，如下图3所示：
![图3：基本模型](https://upload-images.jianshu.io/upload_images/10947003-2ff62a582e2d9462.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
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
![图4：Deep Interest Network结构](https://upload-images.jianshu.io/upload_images/10947003-a4423b7681ec1e24.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
&emsp;&emsp;与基础模型相比较，DIN引入了新的local activation unit，保持了模型的总体结构。具体来说，activation units主要应用于用户的行为特征，主要是为了计算用户对候选广告A的表达（representation），记为<img src="http://latex.codecogs.com/gif.latex?\inline&space;\upsilon&space;_U" title="\upsilon _U" />,如公式（3）所示：
<div align="center">

</div>


## Reference：
1. [《Deep Interest Network for Click-Through Rate Prediction》阅读笔记](https://zhuanlan.zhihu.com/p/30597671)
