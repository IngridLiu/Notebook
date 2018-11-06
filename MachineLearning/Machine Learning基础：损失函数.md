# Machine Learning 基础：损失函数

<br>
<br>

&emsp;&emsp;损失函数是用来估量模型的预测值f(x)与真实值Y的不一致程度，它是一个非负实值函数，通常使用L(Y,f(x))来表示损失函数越小，模型的鲁棒性就越好。损失函数是经验风险函数的核心部分，也是结构风险函数的重要组成部分。模型的结构风险函数包括了经验风险和正则项。通常可以表示成下式：

![](https://img.okay.do/92e490af115aa3663d0172ea536b1310_W433_H96_G0)

&emsp;&emsp;其中，前面的均值函数表示的是经验风险函数，L代表的是损失函数，后面的Φ是正则化项（regularizer）或者叫惩罚项（penalty term），它可以是L1，也可以是L2，或者其他的正则函数。整个式子表示的意思是找到使目标函数最小时的θθ值。下面主要列出几种常见的损失函数。
 
 
## 1 log对数损失函数

&emsp;&emsp;在逻辑回归的推导中，它假设样本服从伯努利分布（0-1分布），然后求得满足该分布的似然函数，接着取对数求极值等等。而逻辑回归并没有求似然函数的极值，而是把极大化当作是一种思想，进而推导出它的经验风险函数为：最小化负的似然函数（即max F(y, f(x)) —-> min -F(y, f(x))），从损失函数的视角来看，它就成了log损失函数了。
 
### 1.1 log损失函数的标准形式
&emsp;&emsp;L(Y,P(Y|X))=-logP(Y|X)

&emsp;&emsp;取对数是为了方便计算极大似然估计，因为在MLE中，直接求导比较困难，所以通常都是先取对数再求导找极值点。损失函数L(Y,P(Y|X))表达的是样本X在分类Y的情况下，使概率P（Y|X）达到最大值，（换言之，就是利用已知的样本分布，找到最有可能（即最大概率）导致这种分布的参数值，或者说什么样的参数才能使我们观测到目前这组数据的概率最大）。因为log函数是单调递增的，所以logP(Y|X）也会达到最大值，因此在前面加上负号之后，最大化P(Y|X)就等于最小化L了。

&emsp;&emsp;逻辑回归(Logistic Regresssion)的P(Y=y|x)的表达式如下（为了将类别标签y统一为1和0,下面将表达式分开表示）：

![](https://img.okay.do/048f3ce30bac817487d93f379d6a7ca5_W445_H62_G0)

&emsp;&emsp;将它带入上式，可以通过推导得到logistic的损失函数表达式，如下：

![](https://img.okay.do/5303f75fe954f2971bbb54084bd28753_W367_H43_G0)

&emsp;&emsp;逻辑回归最后得到的目标式子如下：

![](https://img.okay.do/14ee834acbcb7e260126d9ecc79ec98c_W453_H69_G0)

&emsp;&emsp;上面是针对二分类而言的。
 
 
## 2 平方损失函数（最小二乘，Ordinary Least Squares)

&emsp;&emsp;最小二乘法是线性回归的一种，OLS将问题转化成了一个凸优化问题。在线性回归中，它的假设样本和噪声都服从高斯分布（根据中心极限定理），再通过最小二乘的原则得出最小二乘的式子。最小二乘的原则是：最优拟合直线应该是使各点到回归直线的距离和最小的直线，即平方和最小。换言之，OLS是基于距离的，而这个距离就是我们用的最多的欧几里得距离，选择欧式距离作为误差度量的原因如下：        

- 简单，计算方便；

- 欧氏距离是一种很好的相似性度量标准；

- 在不同的表示域变换后特征性质不变。

&emsp;&emsp;平方损失（Square Loss）的标准形式如下：

![](https://img.okay.do/37e060dca097d8fce7432287b5469981_W204_H57_G0)

&emsp;&emsp;当样本个数为n时，此时的损失函数为：

![](https://img.okay.do/fac3fe4749b4ffffafb614a109dfdc0b_W235_H51_G0)

&emsp;&emsp;Y-f(X)表示的是残差，整个式子表示的是残差的平方和，而我们的目的就是最小化这个目标函数值（注：该式子未加入正则项），也就是最小化残差的平方和（residual sum of squares，RSS）。而在实际应用中，通常会使用均方差（MSE）作为一项衡量指标，公式如下：

![](https://img.okay.do/c7a3fa8ea0f93f2f5951f13aaef380cb_W200_H72_G0)

&emsp;&emsp;上面提到了线性回归，这里额外补充一句，我们通常说的线性有两种情况，一种是因变量y是自变量x的线性函数，一种是因变量y是参数α的线性函数。在机器学习中，通常指的都是后一种情况。
 
 
## 3 指数损失函数（Adaboost）

&emsp;&emsp;学过Adaboost算法的人都知道，它是前向分步加法算法的特例，是一个加和模型，损失函数就是指数函数。在Adaboost中，经过m此迭代之后，可以得到fm(x)：

![](http://latex.codecogs.com/gif.latex?%24%24f_m%20%28x%29%20%3D%20f_%7Bm-1%7D%28x%29%20+%20%5Calpha_m%20G_m%28x%29%24%24)
 
&emsp;&emsp;Adaboost每次迭代时的目的是为了找到最小化下列式子时的参数α和G：

![](http://latex.codecogs.com/gif.latex?%24%24%5Carg%20%5Cmin_%7B%5Calpha%2C%20G%7D%20%3D%20%5Csum_%7Bi%3D1%7D%5E%7BN%7D%20exp%5B-y_%7Bi%7D%20%28f_%7Bm-1%7D%28x_i%29%20+%20%5Calpha%20G%28x_%7Bi%7D%29%29%5D%24%24)
 
&emsp;&emsp;指数损失函数(exp-loss）的标准形式如下：
 
![](http://latex.codecogs.com/gif.latex?L%28y%2C%20f%28x%29%29%20%3D%20%5Cexp%5B-yf%28x%29%5D)
 
&emsp;&emsp;可以看出，Adaboost的目标式子就是指数损失，在给定n个样本的情况下，Adaboost的损失函数为：
 
![](http://latex.codecogs.com/gif.latex?L%28y%2C%20f%28x%29%29%20%3D%20%5Cfrac%7B1%7D%7Bn%7D%5Csum_%7Bi%3D1%7D%5E%7Bn%7D%5Cexp%5B-y_if%28x_i%29%5D)
 
&emsp;&emsp;关于Adaboost的推导，可以参考Wikipedia：AdaBoost或者《统计学习方法》P145.
 
 
## 4  Hinge损失函数（SVM）

&emsp;&emsp;在机器学习算法中，hinge损失函数和SVM是息息相关的。在线性支持向量机中，最优化问题可以等价于下列式子：

![](https://img.okay.do/6bf5a52ab762d431f2c1656d8ec370d9_W306_H69_G0)

&emsp;&emsp;下面来对式子做个变形，令:

![](https://img.okay.do/64fd554fca29b32530adfe449bfc234a_W203_H39_G0)

&emsp;&emsp;于是，原式就变成了：

![](https://img.okay.do/fe31e340bde923d7750870a98b725a28_W243_H87_G0)

&emsp;&emsp;如若取λ=1/2C，式子就可以表示成：

![](https://img.okay.do/fe31e340bde923d7750870a98b725a28_W243_H87_G0)

&emsp;&emsp;可以看出，该式子与下式非常相似：


![](https://img.okay.do/746672704f30e66c26064134ef1b862f_W265_H78_G0)

&emsp;&emsp;前半部分中的ll就是hinge损失函数，而后面相当于L2正则项。
 
&emsp;&emsp;Hinge 损失函数的标准形式

![](https://img.okay.do/1f5101a928e0769717e9290a3aa9b064_W275_H81_G0)

&emsp;&emsp;可以看出，当|y|>=1时，L(y)=0。
 
 
## 5 其他损失函数 

&emsp;&emsp;除了以上这几种损失函数，常用的还有：
 
&emsp;&emsp;0-1损失函数

![](http://latex.codecogs.com/gif.latex?L%28Y%2C%20f%28X%29%29%20%3D%20%5Cleft%5C%7B%5Cbegin%7Bmatrix%7D1%20%2C%26%20Y%20%5Cneq%20f%28X%29%5C%5C%200%20%2C%26%20y%20%3D%20f%28X%29%20%5Cend%7Bmatrix%7D%5Cright.)

&emsp;&emsp;绝对值损失函数

![](http://latex.codecogs.com/gif.latex?L%28Y%2C%20f%28X%29%29%20%3D%20%7CY-f%28X%29%7C)
 
&emsp;&emsp;下面来看看几种损失函数的可视化图像，对着图看看横坐标，看看纵坐标，再看看每条线都表示什么损失函数，多看几次好好消化消化。

![](https://img.okay.do/45fc7ddf4b16ba3c227f5148a8c7c05f_W560_H420_G0)
 

 
参考：

[《机器学习-损失函数》](http://www.csuldw.com/2016/03/26/2016-03-26-loss-function/)
 