# DeepFM: A Factorization-Machine based Neural Network for CTR Prediction
| IJCAI 2017


## 1 DeepFM 论文内容

### 1.1 Abstract

&emsp;&emsp;这篇论文来自哈工大&华为诺亚方舟实验室，主要关注如何学习user behavior背后的组合特征（feature interactions），从而最大化推荐系统的CTR。但目前的方法容易得到low-或者high-order interactions。因此这篇论文提出构建一个端到端的可以同时突出低阶和高阶feature interactions的学习模型DeepFM。DeepFM是一个新的神经网络框架，结合了FM在推荐中的优势和深度学习在特征学习中的优势。
详见：A Factorization-Machine based Neural Network for CTR Prediction

&emsp;&emsp;DeepFM是一个集成了FM和DNN的神经网络框架，思路和Google的Wide&Deep相似，都包括wide和deep两部分。W&D模型的wide部分是广义线性模型，DeepFM的wide部分则是FM模型，两者的deep部分都是深度神经网络。DeepFM神经网络部分，隐含层的激活函数用ReLu和Tanh做信号非线性映射，Sigmoid函数做CTR预估的输出函数。

![](https://upload-images.jianshu.io/upload_images/10947003-8d64e3901003ebd5.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

&emsp;&emsp;W&D模型的输入向量维度很大，因为wide部分的特征包括了手工提取的pairwise特征组合，大大提高计算复杂度。和W&D模型相比，DeepFM的wide和deep部分共享相同的输入，可以提高训练效率，不需要额外的特征工程，用FM建模low-order的特征组合，用DNN建模high-order的特征组合，因此可以同时从raw feature中学习到low-和high-order的feature interactions。在真实应用市场的数据和criteo的数据集上实验验证，DeepFM在CTR预估的计算效率和AUC
、LogLoss上超越了现有的模型（LR、FM、FNN、PNN、W&D）。

<br>

### 1.2 研究背景

&emsp;&emsp;推荐系统中的CTR预估是预测用户点击推荐物品的概率。大部分推荐系统的目标是最大化点击次数，因此要推荐给用户的物品的排序策略，直接按预估的CTR大小排序即可；但在其他场景如在线广告，目标是最大化收益，因此排序策略调整为按所有候选item的CTR*bid，bid是item被user点击后系统的收益。两种场景的关键都是要准确预估CTR。

&emsp;&emsp;论文作者观察app market发现，一些order-2 interaction（如app category和time-stamp）、order-3 interaction（user gender、age和app category）都可以作为CTR的signal。因此，low-order和high-order的feature interactions都可以在CTR预估中发挥作用。但如何有效构建interactions呢？大部分的特征组合隐藏在数据中，难以发现关联关系，只能通过机器学习来自动挖掘。

<br>

### 1.3 相关工作

&emsp;&emsp;FTRL算法（McMahan et al. 2013），generalized linear model虽然简单，但实践中很有效果。但这类线性模型难以学习组合特征，一般需要手动构建特征向量，难以处理高阶组合或者没有出现在训练数据中的组合。

&emsp;&emsp;Factorization Machine模型（Rendle 2010），对特征之间进行向量内积，实现特征们的逐对组合pairwise interactions。理论上FM可以对高阶特征组合建模，但实践中只用order-2特征因为其高复杂度。

&emsp;&emsp;DNN在特征表示学习中很有效果，可以用来学习组合特征。

&emsp;&emsp;（Liu et al., 2015）和（Zhang et al., 2014）扩展CNN和RNN用于CTR预估，但CNN-based模型对领域特征有偏biased，RNN-based模型适合用在有时序依赖的点击数据。

&emsp;&emsp;Factorization-machine supported Neural Network（FNN）（Zhang et al., 2016），在使用DNN前预训练FM，因此限制了FM的能力。

&emsp;&emsp;Product-based Neural Network（PNN）（Qu et al., 2016）在DNN的embedding层和全连接层之间引入product层，来研究feature interactions。

&emsp;&emsp;Wide & Deep模型(Cheng et al., 2016)认为，PNN/FNN和其他Deep模型提取很少low-order的feature interactions，提出的W&D模型可以同时对low-order和high-order建模，但要对wide和deep部分模型分别输入，其中wide部分还需要人工特征工程。

&emsp;&emsp;FNN vs PNN vs W&D

![](https://upload-images.jianshu.io/upload_images/10947003-ff4d41daf9417f70.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/10947003-12d93fda74139668.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/400)

&emsp;&emsp;FNN：图5左边，预训练FM再前馈NN，有缺陷：embedding参数被FM影响；pre-training阶段效率低；FNN只捕获high-order特征组合（low-order特征对CTR很重要）

&emsp;&emsp;PNN：图5中间，引入product层来捕获high-order特征组合，根据不同的product操作有三种变体IPNN（inner product）、OPNN（outer product）、PNN*（inner & outer）。缺陷：outer product丢失太多信息，不太可靠；inner product更可信，但product层输出全连接到第一隐含层的所有神经元，计算复杂度还是太高（DeepFM只在连接到最后输出层的一个神经元）；PNN和FNN一样忽视low-order特征组合。

&emsp;&emsp;W&D：对于Wide部分需要人工特征工程。

<br>

### 1.4 DeepFM 模型

#### 1.4.1 FM部分

![](https://upload-images.jianshu.io/upload_images/10947003-9631ce5d8c7bf4f3.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/800)

&emsp;&emsp;在FM模型中，特征i和特征j的组合通过计算各自的隐含向量Vi和Vj的inner product得到。无论i或者j是否在训练数据中出现，隐含向量Vi或Vj都可以被FM训练得到。

![](https://upload-images.jianshu.io/upload_images/10947003-f6728cdd615e4430.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/800)


#### 1.4.2 Deep部分

![](https://upload-images.jianshu.io/upload_images/10947003-b12a4c4ae2874bf2.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/800)

&emsp;&emsp;Deep部分是一个前馈神经网络，用于学习high-order特征。论文提到了何凯明CVPR2016的用于图像识别的深度残差网络和Boulanger-Lewandowski的识别语音的RNN，输入的向量都是连续取值、稠密的。而CTR预估的输入向量则不同，raw feature input一般是高度稀疏（每个field

&emsp;&emsp;vector只有一个非零取值）、超高维度（userID的field vector就接近上亿维）、混合categorical和continuous取值、被分组到一系列field（如性别、位置、年龄）。因此需要设计一个embedding层（图4），压缩输入向量到一个低维稠密实值的向量，再feeding到第一个hidden层，否则神经网络难以训练。

![embedding layer](https://upload-images.jianshu.io/upload_images/10947003-41ae64ae935e50d0.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/400)

&emsp;&emsp;embedding层的设计：（1）对于不同长度的输入field向量，得到的embedding长度都是k；（2）FM中的隐含向量V现在作为神经网络的权重，被学习来压缩输入field向量到embedding向量。embedding层的输出是m个field对应的e向量，传入DNN，最后得到一个稠密实值向量，经过一个sigmoid函数得到预测的CTR。


<br>
<br>
<br>

## Reference:
1. [DeepFM: A Factorization-Machine based Neural Network for CTR Prediction, IJCAI 2017](https://zhuanlan.zhihu.com/p/27999355)
2. [DeepFM的tensorflow实现](https://github.com/ChenglongChen/tensorflow-DeepFM)
3. [ctr预估之DeepFM](https://zhuanlan.zhihu.com/p/32563337)
3. [deep-ctr](https://github.com/charleshm/deep-ctr)