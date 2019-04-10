# Siamese Network 孪生神经网络

<br>
<br>

## 1. Siamese Network用途

&emsp;&emsp;Siamese Network是一种用来进行相似性度量的方法，当类别数多，但每个类别的样本数量少的情况下可用于类别的识别、分类等。

&emsp;&emsp;传统的用于区分的分类方法是需要确切地知道每个样本属于哪个类，需要针对样本有确切地标签。而且相对来说，标签地数量是不会太多的。当类别数过多，每个类别的样本数又相对较少的情况下，这些方法就不那么适用了。**Siamese网络从数据中去学习一个相似性度量**，用这个学习出来的度量去比较和匹配新的未知类别的样本。这个方法能被应用于那些类别数多或者整个训练样本无法用于之前方法训练的分类问题。

## 2. Siamese Network主要思想

&emsp;&emsp;Siamese Network是通过一个函数将输入映射到目标空间，在目标空间使用简单的距离（欧式距离等）进行对比相似度。训练目标是最小化来自相同类别的一对样本的损失函数值，最大化来自不同类别的一堆样本的损失函数值。

&emsp;&emsp;给定一组映射函数

![公式1](https://img-blog.csdn.net/20180726091337562?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3NoZW56aWhlbmcx/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)，

&emsp;&emsp;其中参数分别为权重w和偏好b。

&emsp;&emsp;Siamese Network的目的就是寻找这样的一系列参数w,b,使得当X1和X2来自同一个类别时（或者是最相似时），损失函数（空间距离）如公式2取得极小值；当样本X1`和X2`来自不同的类别时（或者是不相似），损失函数（空间距离）（如公式2）取得极大值。因此，孪生网络需要用一对图像进行训练，这里的是一切可以满足可微分条件的函数。因为针对成对样本输入，这里两个相同的函数φ(·)，拥有一份相同的参数w,b，即这个结构是对称的，我们将它叫做siamese architecture。 

![公式2](https://img-blog.csdn.net/20180726091818360?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3NoZW56aWhlbmcx/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

## 3. 网络结构

&emsp;&emsp;作者用的网络结构非常的简单，如下：

![](https://img-blog.csdn.net/20180726093057424?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3NoZW56aWhlbmcx/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

&emsp;&emsp;作者采用的是权重共享的方式，而且作者并没有使用偏置b。图中的Gw和我们前文的Sw,b指的是一个事。

&emsp;&emsp;训练过程中，输入的是一对图像和他们的标签(X1,X2,Y)。其中Y=0表示X1和X2属于同一属性图像，Y=1则表示非同一属性图片。即相同对为（X1,X2,0）,欺骗对为（X1,X2’,1）针对两个不同的输入X1和X2，分别输出特征空间结果为:

![](https://img-blog.csdn.net/20180726093932398?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3NoZW56aWhlbmcx/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

&emsp;&emsp;然后对这两个结果使用能量函数进行判断。能量函数设计如下：

![](https://img-blog.csdn.net/20180726094231749?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3NoZW56aWhlbmcx/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

## 4. 损失函数

&emsp;&emsp;假设损失函数只与输入的图相对、标签、网络权重相关（w，x_1, x_2, Y）。那么损失函数可以定义为如下形式：

![](https://img-blog.csdn.net/20180726095513156?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3NoZW56aWhlbmcx/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

&emsp;&emsp;其中，L_G表示相同类别相似度测度；L_l表示不同类别相似度测度。n表示为训练样本。

&emsp;&emsp;通过这样分开设计，我们可以在最小化损失函数的时候，减少相同类别对的能量，增加不相同对的能量。很简单只管直观的方法实现这个的话，我们只要将L_G设计成单调增加，让L_l单调递减就可以了。但是我们需要保证一个前提就是，不相同的图片对距离肯定要比不相同图片对距离大，那么要满足：

![](https://img-blog.csdn.net/20180726101419137?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3NoZW56aWhlbmcx/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

&emsp;&emsp;最后作者给出一个精确的对单个样本的损失函数： 

![](https://img-blog.csdn.net/20180726101639372?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3NoZW56aWhlbmcx/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

## 5. Siamese network的用途有哪些？

&emsp;&emsp;这个可以说太多了，nlp&cv领域都有很多应用。

&emsp;&emsp;前面提到的词汇的语义相似度分析，QA中question和answer的匹配，签名/人脸验证。

&emsp;&emsp;手写体识别也可以用siamese network，网上已有github代码。

&emsp;&emsp;还有kaggle上Quora的question pair的比赛，即判断两个提问是不是同一问题，冠军队伍用的就是n多特征+Siamese network，知乎团队也可以拿这个模型去把玩一下。

&emsp;&emsp;在图像上，基于Siamese网络的视觉跟踪算法也已经成为热点《Fully-convolutional siamese networks for object tracking》。


<br>
<br>
<br>
<br>



## Reference：

1. [Learning a similarity metric discriminatively, with application to face verification. ](http://yann.lecun.com/exdb/publis/pdf/chopra-05.pdf)

2. [Siamese Network （原理篇）](https://blog.csdn.net/shenziheng1/article/details/81213668)

3. [Facial Similarity with Siamese Networks in Pytorch](https://github.com/harveyslash/Facial-Similarity-with-Siamese-Networks-in-Pytorch)

4. [Siamese network 孪生神经网络--一个简单神奇的结构](https://zhuanlan.zhihu.com/p/35040994)