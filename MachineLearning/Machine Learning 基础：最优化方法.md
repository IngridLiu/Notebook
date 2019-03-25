# Machine Learning 基础：最优化方法

<br>
<br>


## 1. 梯度下降算法(GD)

下面的h(x)是要拟合的函数，J(theta)损失函数，theta是参数，要迭代求解的值，theta求解出来了那最终要拟合的函数h(theta)就出来了。其中m是训练集的记录条数，j是参数的个数。

![](https://img-blog.csdn.net/20130525190050025)

![](https://img-blog.csdn.net/20130525190305253)
 
## 2. 批量梯度下降((Batch gradient descent))

(1) 将J(theta)对theta求偏导，得到每个theta对应的梯度

![](https://img-blog.csdn.net/20130525190603437)

(2) 由于是要最小化风险函数，所以按每个参数theta的梯度负方向，来更新每个theta

![](https://img-blog.csdn.net/20130525190954867)

批量梯度下降每次学习都使用整个训练集，因此其优点在于每次更新都会朝着正确的方向进行，最后能够保证收敛于极值点(凸函数收敛于全局极值点，非凸函数可能会收敛于局部极值点)，但是其缺点在于每次学习时间过长，并且如果训练集很大以至于需要消耗大量的内存，并且全量梯度下降不能进行在线模型参数更新。


<br>

## 3. 随机梯度下降

随机梯度下降算法每次从训练集中随机选择一个样本来进行学习。批量梯度下降算法每次都会使用全部训练样本，因此这些计算是冗余的，因为每次都使用完全相同的样本集。而随机梯度下降算法每次只随机选择一个样本来更新模型参数，因此每次的学习是非常快速的，并且可以进行在线更新。

随机梯度下降最大的缺点在于每次更新可能并不会按照正确的方向进行，因此可以带来优化波动(扰动)，

不过从另一个方面来看，随机梯度下降所带来的波动有个好处就是，对于类似盆地区域（即很多局部极小值点）那么这个波动的特点可能会使得优化的方向从当前的局部极小值点跳到另一个更好的局部极小值点，这样便可能对于非凸函数，最终收敛于一个较好的局部极值点，甚至全局极值点。

由于波动，因此会使得迭代次数（学习次数）增多，即收敛速度变慢。不过最终其会和全量梯度下降算法一样，具有相同的收敛性，即凸函数收敛于全局极值点，非凸损失函数收敛于局部极值点。

<br>

## 4. 小批量梯度下降(Mini-batch gradient descent)

Mini-batch 梯度下降综合了 batch 梯度下降与 stochastic 梯度下降，在每次更新速度与更新次数中间取得一个平衡，其每次更新从训练集中随机选择 m,m<n 个样本进行学习。

相对于随机梯度下降，Mini-batch梯度下降降低了收敛波动性，即降低了参数更新的方差，使得更新更加稳定。相对于全量梯度下降，其提高了每次学习的速度。并且其不用担心内存瓶颈从而可以利用矩阵运算进行高效计算。一般而言每次更新随机选择[50,256]个样本进行学习，但是也要根据具体问题而选择，实践中可以进行多次试验，选择一个更新速度与更次次数都较适合的样本数。mini-batch梯度下降可以保证收敛性，常用于神经网络中。

<br>

## 5. 使用动量Momentum(动量)的随机梯度下降（SGD）

&emsp;&emsp;1.动量方法主要是为了解决Hessian矩阵病态条件问题（直观上讲就是梯度高度敏感于参数空间的某些方向）的。

&emsp;&emsp;2.加速学习

&emsp;&emsp;3.一般将参数设为0.5,0.9，或者0.99，分别表示最大速度2倍，10倍，100倍于SGD的算法。

&emsp;&emsp;4.通过速度v，来积累了之间梯度指数级衰减的平均，并且继续延该方向移动： 

![](https://img-blog.csdn.net/20170521223752521?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvQlZMMTAxMDExMTE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

### 5.1 使用动量Momentum(动量)的随机梯度下降（SGD）算法

![使用动量Momentum(动量)的随机梯度下降（SGD）](https://img-blog.csdn.net/20170521224015304?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvQlZMMTAxMDExMTE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

### 5.2 动量算法直观效果解释：

&emsp;&emsp;如图所示，红色为SGD+Momentum。黑色为SGD。可以看到黑色为典型Hessian矩阵病态的情况，相当于大幅度的徘徊着向最低点前进。 
  
&emsp;&emsp;而由于动量积攒了历史的梯度，如点P前一刻的梯度与当前的梯度方向几乎相反。因此原本在P点原本要大幅徘徊的梯度，主要受到前一时刻的影响，而导致在当前时刻的梯度幅度减小。 
  
&emsp;&emsp;直观上讲就是，要是当前时刻的梯度与历史时刻梯度方向相似，这种趋势在当前时刻则会加强；要是不同，则当前时刻的梯度方向减弱。 

![](https://img-blog.csdn.net/20170521224208507?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvQlZMMTAxMDExMTE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)




<br>
<br>
<br>
<br>

## Reference:

1. [Deep Learning 之 最优化方法](https://blog.csdn.net/BVL10101111/article/details/72614711)