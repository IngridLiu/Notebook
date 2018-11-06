# Machine Learning基础：softmax函数

<br>
<br>
<br>
<br>

## 1. softmax函数介绍

&emsp;&emsp;softmax用于多分类过程中，它将多个神经元的输出，映射到（0,1）区间内，可以看成概率来理解，从而来进行多分类！

&emsp;&emsp;假设我们有一个数组，V，Vi表示V中的第i个元素，那么这个元素的softmax值就是

![](https://pic4.zhimg.com/80/v2-65035de6fdfd8b2f13b930191e9a548b_hd.jpg)

&emsp;&emsp;更形象的如下图表示：

![](https://pic4.zhimg.com/80/v2-11758fbc2fc5bbbc60106926625b3a4f_hd.jpg)

## 2 softmax相关求导

&emsp;&emsp;当我们对分类的Loss进行改进的时候，我们要通过梯度下降，每次优化一个step大小的梯度，这个时候我们就要求Loss对每个权重矩阵的偏导，然后应用链式法则。那么这个过程的第一步，就是对softmax求导传回去，不用着急，我后面会举例子非常详细的说明。在这个过程中，你会发现用了softmax函数之后，梯度求导过程非常非常方便！

&emsp;&emsp;下面我们举出一个简单例子，原理一样，目的是为了帮助大家容易理解！

![](https://pic4.zhimg.com/80/v2-d958d4c9d262fdbf799a2010d2f2ee3b_hd.jpg)

&emsp;&emsp;我们能得到下面公式：

&emsp;&emsp;z4 = w41*o1+w42*o2+w43*o3

&emsp;&emsp;z5 = w51*o1+w52*o2+w53*o3

&emsp;&emsp;z6 = w61*o1+w62*o2+w63*o3

&emsp;&emsp;z4,z5,z6分别代表结点4,5,6的输出，01,02,03代表是结点1,2,3往后传的输入.

&emsp;&emsp;那么我们可以经过softmax函数得到

![](http://www.zhihu.com/equation?tex=a_%7B4%7D%3D+%5Cfrac%7Be%5E%7Bz4%7D+%7D%7Bz%5E%7Bz4%7D%2Bz%5E%7Bz5%7D%2Bz%5E%7Bz6%7D%7D+)

![](http://www.zhihu.com/equation?tex=a_%7B5%7D+%3D%5Cfrac%7Be%5E%7Bz5%7D+%7D%7Bz%5E%7Bz4%7D%2Bz%5E%7Bz5%7D%2Bz%5E%7Bz6%7D%7D+)

![](http://www.zhihu.com/equation?tex=a_%7B6%7D%3D+%5Cfrac%7Be%5E%7Bz6%7D+%7D%7Bz%5E%7Bz4%7D%2Bz%5E%7Bz5%7D%2Bz%5E%7Bz6%7D%7D+)

&emsp;&emsp;要使用梯度下降，肯定需要一个损失函数，这里我们使用交叉熵作为我们的损失函数,交叉熵函数形式如下：

![](https://upload-images.jianshu.io/upload_images/10947003-1ba23920743fe0a2.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/200)

&emsp;&emsp;利用链式法则求导,举个例子此时求w41的偏导为：

![](https://pic4.zhimg.com/80/v2-a1041435eb26ff6a38e82b355706ec37_hd.jpg)

&emsp;&emsp;w51.....w63等参数的偏导同理可以求出，那么我们的关键就在于Loss函数对于结点4,5,6的偏导怎么求，如下：

&emsp;&emsp;这里分为俩种情况：

&emsp;&emsp;第一种情况为j=i的情况：

![](https://pic2.zhimg.com/80/v2-d3a4e22a107052ee998823b24b49db71_hd.jpg)

&emsp;&emsp;第二种情况为j!=i的情况：

![](https://pic3.zhimg.com/80/v2-5eafb4c0a835bc90248766ac0c123dfe_hd.jpg)




## Reference:

1. [详解softmax函数以及相关求导过程](https://zhuanlan.zhihu.com/p/25723112)