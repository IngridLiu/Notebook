# Logistic Regression 原理及实现

<br>
<br>

## 1 模型介绍

### 1.1 sigmoid函数

&emsp;&emsp;在介绍逻辑回归模型之前，我们先引入sigmoid函数，其数学形式是：

![](https://upload-images.jianshu.io/upload_images/10947003-28af4aa1e4464916.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/200)

&emsp;&emsp;对应的函数曲线如下图所示：

![](https://upload-images.jianshu.io/upload_images/10947003-4df649d87c1f92bb.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/400)

&emsp;&emsp;从上图可以看到sigmoid函数是一个s形的曲线，它的取值在[0, 1]之间，在远离0的地方函数的值会很快接近0/1。这个性质使我们能够以概率的方式来解释（后边延伸部分会简单讨论为什么用该函数做概率建模是合理的)。

### 1.2 决策函数

&emsp;&emsp;一个机器学习的模型，实际上是把决策函数限定在某一组条件下，这组限定条件就决定了模型的假设空间。当然，我们还希望这组限定条件简单而合理。而逻辑回归模型所做的假设是：

![](https://upload-images.jianshu.io/upload_images/10947003-6b26ccea4e16f5bc.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/400)

&emsp;&emsp;这里的g(h)是上边提到的 sigmoid 函数，相应的决策函数为：

![](https://upload-images.jianshu.io/upload_images/10947003-5cf4767b93d8e88b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/200)

&emsp;&emsp;选择0.5作为阈值是一个一般的做法，实际应用时特定的情况可以选择不同阈值，如果对正例的判别准确性要求高，可以选择阈值大一些，对正例的召回要求高，则可以选择阈值小一些。

### 1.3 参数求解

&emsp;&emsp;模型的数学形式确定后，剩下就是如何去求解模型中的参数。统计学中常用的一种方法是最大似然估计，即找到一组参数，使得在这组参数下，我们的数据的似然度（概率）越大。在逻辑回归模型中，似然度可表示为：

![](https://upload-images.jianshu.io/upload_images/10947003-43009a148b3b675b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/400)

&emsp;&emsp;取对数可以得到对数似然度：

![](https://upload-images.jianshu.io/upload_images/10947003-b25bfe3dd74abacd.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/400)

&emsp;&emsp;另一方面，在机器学习领域，我们更经常遇到的是损失函数的概念，其衡量的是模型预测错误的程度。常用的损失函数有0-1损失，log损失，hinge损失等。其中log损失在单个数据点上的定义为−ylogp(y|x)−(1−y)log1−p(y|x)

&emsp;&emsp;如果取整个数据集上的平均log损失，我们可以得到

![](https://upload-images.jianshu.io/upload_images/10947003-d0e33c38e39c31aa.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/200)

&emsp;&emsp;即在逻辑回归模型中，我们最大化似然函数和最小化log损失函数实际上是等价的。对于该优化问题，存在多种求解方法，这里以梯度下降的为例说明。梯度下降(Gradient Descent)又叫作最速梯度下降，是一种迭代求解的方法，通过在每一步选取使目标函数变化最快的一个方向调整参数的值来逼近最优值。基本步骤如下：

![](https://upload-images.jianshu.io/upload_images/10947003-2b347367f51d1f0a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/800)

&emsp;&emsp;沿梯度负方向选择一个较小的步长可以保证损失函数是减小的，另一方面，逻辑回归的损失函数是凸函数（加入正则项后是严格凸函数），可以保证我们找到的局部最优值同时是全局最优。此外，常用的凸优化的方法都可以用于求解该问题。例如共轭梯度下降，牛顿法，LBFGS等。

### 1.4 分类边界

&emsp;&emsp;知道如何求解参数后，我们来看一下模型得到的最后结果是什么样的。很容易可以从sigmoid函数看出，当θT*x>0时，y=1，否则 y=0。θT*x=0是模型隐含的分类平面（在高维空间中，我们说是超平面）。所以说逻辑回归本质上是一个线性模型，但是，这不意味着只有线性可分的数据能通过LR求解，实际上，我们可以通过特征变换的方式把低维空间转换到高维空间，而在低维空间不可分的数据，到高维空间中线性可分的几率会高一些。下面两个图的对比说明了线性分类曲线和非线性分类曲线（通过特征映射）。

![](https://upload-images.jianshu.io/upload_images/10947003-cd286b088a6f01b9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/600)

&emsp;&emsp;左图是一个线性可分的数据集，右图在原始空间中线性不可分，但是在特征转换 [x1,x2]=>[x1,x2,x1^2,x2^2,x1x2]后的空间是线性可分的，对应的原始空间中分类边界为一条类椭圆曲线。

### 1.5 正则化

&emsp;&emsp;当模型的参数过多时，很容易遇到过拟合的问题。这时就需要有一种方法来控制模型的复杂度，典型的做法在优化目标中加入正则项，通过惩罚过大的参数来防止过拟合：

![](https://upload-images.jianshu.io/upload_images/10947003-20f0bb50c2e9c5d4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/400)

&emsp;&emsp;一般情况下，取p=1或p=2，分别对应L1，L2正则化，两者的区别可以从下图中看出来，L1正则化（左图）倾向于使参数变为0，因此能产生稀疏解。

![](https://upload-images.jianshu.io/upload_images/10947003-8443af111153e6ef.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/600)

&emsp;&emsp;实际应用时，由于我们数据的维度可能非常高，L1正则化因为能产生稀疏解，使用的更为广泛一些。


<br>

## 2. 延伸与扩展

### 2.1 多分类(softmax)

&emsp;&emsp;如果y不是在[0,1]中取值，而是在K个类别中取值，这时问题就变为一个多分类问题。有两种方式可以出处理该类问题：一种是我们对每个类别训练一个二元分类器（One-vs-all），当K个类别不是互斥的时候，比如用户会购买哪种品类，这种方法是合适的。如果K个类别是互斥的，即 y=i的时候意味着y不能取其他的值，比如用户的年龄段，这种情况下 Softmax 回归更合适一些。Softmax 回归是直接对逻辑回归在多分类的推广，相应的模型也可以叫做多元逻辑回归（Multinomial Logistic Regression）。模型通过 softmax 函数来对概率建模，具体形式如下：

![](https://upload-images.jianshu.io/upload_images/10947003-6d9722594a220ee8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/200)

&emsp;&emsp;而决策函数为：

![](https://upload-images.jianshu.io/upload_images/10947003-2e8ad17e3273feb9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/200)

&emsp;&emsp;对应的损失函数为：

![](https://upload-images.jianshu.io/upload_images/10947003-40f28b63c1b6c306.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/400)

### 2.2 非线性分类器

&emsp;&emsp;可以使用核函数。

<br>

## 3. 逻辑回归与其他模型的关系

### 3.1 逻辑回归与线性回归

&emsp;&emsp;在线性回归中，一旦出现离群点，它会导致学习到的线性函数偏离(它产生的权重改变量会比较大)，从而原先设定的0.5阈值就不好用了，此时要么调整阈值要么调整线性函数。如果我们调节阈值，在这个图里线性函数取值看起来是0～1，但是在其他情况下可能就是从−∞到∞所以阈值的大小很难确定。而使用sigmoid函数，将wx+b值映射到了(0,1)，并且解释成概率。而如果调节线性函数，那么最需要的是减少离群点的影响，离群点往往会导致比较大的|wx+b|值，通过sigmoid函数刚好能够削弱这种类型值的影响，这种值经过sigmoid之后接近0或者1,且偏导数较小。

&emsp;&emsp;因此可以说sigmoid在逻辑回归中起到了两个作用，一是将线性函数的结果映射到了(0,1)，一是减少了离群点的影响。

&emsp;&emsp;线性回归是在拟合输入向量x的分布，而逻辑回归中的线性函数是在拟合决策边界，它们的目标是不一样的。

&emsp;&emsp;总之，线性回归和逻辑回归是属于同一种模型，但是它们要解决的问题不一样，前者解决的是regression问题，后者解决的是classification问题，前者的输出是连续值，后者的输出是离散值，而且前者的损失函数是输出y的高斯分布，后者损失函数是输出的伯努利分布。


### 3.2 逻辑回归与svm

&emsp;&emsp;逻辑回归和svm作为经典的分类算法，被放在一起讨论的次数特别多，知乎和Quora上每种意见都非常有意思都从不同角度有分析，建议都可以看看[14][15][16]。这里只讨论一些我赞同的观点。要是不清楚svm的由来，建议看JerryLead的系列博客[17]，我这里就不提了。

&emsp;&emsp;**相同点:**

&emsp;&emsp;都是分类算法

&emsp;&emsp;都是监督学习算法

&emsp;&emsp;都是判别模型

&emsp;&emsp;都能通过核函数方法针对非线性情况分类

&emsp;&emsp;目标都是找一个分类超平面

&emsp;&emsp;都能减少离群点的影响

&emsp;&emsp;**不同点:**

&emsp;&emsp;损失函数不同，逻辑回归是cross entropy loss，svm是hinge loss

&emsp;&emsp;逻辑回归在优化参数时所有样本点都参与了贡献，svm则只取离分离超平面最近的支持向量样本。这也是为什么逻辑回归不用核函数，它需要计算的样本太多。并且由于逻辑回归受所有样本的影响，当样本不均衡时需要平衡一下每一类的样本个数。

&emsp;&emsp;逻辑回归对概率建模，svm对分类超平面建模

&emsp;&emsp;逻辑回归是处理经验风险最小化，svm是结构风险最小化。这点体现在svm自带L2正则化项，逻辑回归并没有

&emsp;&emsp;逻辑回归通过非线性变换减弱分离平面较远的点的影响，svm则只取支持向量从而消去较远点的影响

&emsp;&emsp;逻辑回归是统计方法，svm是几何方法

### 3.3 逻辑回归与朴素贝叶斯

&emsp;&emsp;这两个算法有一些相似之处，并且在对比判别模型和生成模型，它们作为典型的分类算法经常被提及，因此这里也做一个小小的总结。

&emsp;&emsp;相同点是，它们都能解决分类问题和都是监督学习算法。此外，有意思的是，当假设朴素贝叶斯的条件概率P(X|Y=ck)服从高斯分布时Gaussian Naive Bayes，它计算出来的P(Y=1|X)形式跟逻辑回归是一样的。

&emsp;&emsp;不同的地方在于，逻辑回归为判别模型求的是p(y|x)，朴素贝叶斯为生成模型求的是p(x,y)。前者需要迭代优化，后者不需要。在数据量少的情况下后者比前者好，数据量足够的情况下前者比后者好。由于朴素贝叶斯假设了条件概率P(X|Y=ck)是条件独立的，也就是每个特征权重是独立的，如果数据不符合这个情况，朴素贝叶斯的分类表现就没有逻辑回归好。

<br>

## 4. 逻辑回归实现

### 4.1 逻辑回归Python实现

```python
# code resource: https://github.com/RRdmlearning/Machine-Learning-From-Scratch/blob/master/logistic_regression/logistic_regression.py

from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
import numpy as np


# sigmoid函数
def sigmoid(x):
    return 1 / (1 + np.exp(x))

class LogisticRegression():
    """
        Params:
            n_iterations: int, 学习的轮数
            learnging_rate: float, 梯度下降的学习率
    """

    def __init__(self, learning_rate = .1, n_iterations = 4000):
        self.learning_rate = learning_rate
        self.n_iterations = n_iterations

    def init_weights(self, n_features):
        # 初始化参数
        # 参数范围(-1/sqrt(N), 1/sqrt(N))
        limit = np.sqrt(1/n_features)
        w = np.random.uniform(-limit, limit, (n_features, 1))
        b = 0
        self.w = np.insert(w, 0, b, axis=0)

    def fit(self, X, y):
        # 训练模型
        m_samples, n_features = X.shape
        self.init_weights(n_features)
        # 为X增加一列特征x1,x1 = 1
        X = np.insert(X, 0, 1, axis=1)
        y = np.reshape(y, (m_samples, 1))

        # 梯度训练n_interations轮
        for i in range(self.n_iterations):
            h_x = X.dot(self.w)
            y_pred = sigmoid(h_x)
            w_grad = X.T.dot(y_pred - y)    # 求梯度
            self.w = self.w - self.learning_rate * w_grad

    def predict(self, X):
        # 预测
        X = np.insert(X, 0, 1, axis=1)
        h_x = X.dot(self.w)
        y_pred = np.round(sigmoid(h_x))
        return y_pred.astype(int)

def main():
    # load dataset
    data = datasets.load_iris()
    X = data.data[data.target != 0]/np.linalg.norm(data.data[data.target != 0], axis=0)
    y = data.target[data.target != 0]
    y[y == 1] = 0
    y[y == 2] = 1

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)

    clf = LogisticRegression()
    clf.fit(X_train, y_train)
    y_pred = clf.predict(X_test)
    y_pred = np.reshape(y_pred, y_test.shape)
    accuracy = accuracy_score(y_test, y_pred)
    print("Accuracy:", accuracy)


if __name__ == "__main__":
    main()
```

### 4.2 逻辑回归的sklearn实现

#### 4.2.1 逻辑回归的sklearn实现

```python
import numpy as np
import matplotlib.pyplot as plt

# 使用交叉验证的方法，把数据集分为训练集合测试集
from sklearn.model_selection import train_test_split

from sklearn import datasets
from sklearn.linear_model import LogisticRegression

# 加载iris数据集
def load_data():
    diabetes = datasets.load_iris()

    # 将数据集拆分为训练集和测试集 
    X_train, X_test, y_train, y_test = train_test_split(
    diabetes.data, diabetes.target, test_size=0.30, random_state=0)
    return X_train, X_test, y_train, y_test

# 使用LogisticRegression考察线性回归的预测能力
def test_LogisticRegression(X_train, X_test, y_train, y_test):
    # 选择模型
    cls = LogisticRegression()

    # 把数据交给模型训练
    cls.fit(X_train, y_train)

    print("Coefficients:%s, intercept %s"%(cls.coef_,cls.intercept_))
    print("Residual sum of squares: %.2f"% np.mean((cls.predict(X_test) - y_test) ** 2))
    print('Score: %.2f' % cls.score(X_test, y_test))

if __name__=='__main__':
    X_train,X_test,y_train,y_test=load_data() # 产生用于回归问题的数据集
    test_LogisticRegression(X_train,X_test,y_train,y_test) # 调用 test_LinearRegression

```

#### 4.2.2 sklearn.linear_model.LogisticRegression参数详解
```
class sklearn.linear_model.LogisticRegression(
  penalty='l2', 
  dual=False,
  tol=0.0001,
  C=0.1,
  fit_intercept=True,
  intercept_cscaling=1,
  class_weight=None,
  random_state=None,
  solver='liblinear',
  max_iter=100,
  multi_class='ovr',
  verbose=0,
  warm_start=False,
  n_jobs=1)
```

&emsp;&emsp;Logistic Regression分类器。

&emsp;&emsp;在多分类的情况下，若将'multi_class'设为'ovr'，则训练算法为one-vs-rest（OvR）；若将‘mulit_class’设为‘ovr’则使用交叉熵损失。目前‘multinomial’选项仅支持‘lbfgs’、‘sag’、‘newton-cg’等solvers。

&emsp;&emsp;该分类器使用‘liblinear’library，‘newton-cg’，‘sag’和‘lbfgs’等slovers。该分类器能够处理密集和稀疏型输入。处理C-ordered arrays或者包含64-bit的浮点型数据的CSR matrices作为输入，其他类型的输入数据都将被转换（和复制）。

&emsp;&emsp;‘newton-cg’，‘sag’和‘lbfgs’等solvers仅支持‘L2’regularization，‘liblinear’ solver同时支持‘L1’、‘L2’regularization，若dual=Ture，则仅支持L2 penalty。


##### 4.2.2.1Parameters 参数详解

**penalty** : str, ‘l1’ or ‘l2’, default: ‘l2’

>Used to specify the norm used in the penalization. The ‘newton-cg’, ‘sag’ and ‘lbfgs’ solvers support only l2 penalties.

New in version 0.19: l1 penalty with SAGA solver (allowing ‘multinomial’ + L1)- 

>&emsp;&emsp;惩罚项，str类型，可选参数为l1和l2，默认为l2。用于指定惩罚项中使用的规范。newton-cg、sag和lbfgs求解算法只支持L2规范。L1G规范假设的是模型的参数满足拉普拉斯分布，L2假设的模型参数满足高斯分布，所谓的范式就是加上对参数的约束，使得模型更不会过拟合(overfit)，但是如果要说是不是加了约束就会好，这个没有人能回答，只能说，加约束的情况下，理论上应该可以获得泛化能力更强的结果。

 &emsp;&emsp;调参经验：
 
>&emsp;&emsp;LogisticRegression和LogisticRegressionCV默认就带了正则化项。penalty参数可选择的值为"l1"和"l2".分别对应L1的正则化和L2的正则化，默认是L2的正则化。

&emsp;&emsp;在调参时如果我们主要的目的只是为了解决过拟合，一般penalty选择L2正则化就够了。但是如果选择L2正则化发现还是过拟合，即预测效果差的时候，就可以考虑L1正则化。另外，如果模型的特征非常多，我们希望一些不重要的特征系数归零，从而让模型系数稀疏化的话，也可以使用L1正则化。

&emsp;&emsp;penalty参数的选择会影响我们损失函数优化算法的选择。即参数solver的选择，如果是L2正则化，那么4种可选的算法{‘newton-cg’, ‘lbfgs’, ‘liblinear’, ‘sag’}都可以选择。但是如果penalty是L1正则化的话，就只能选择‘liblinear’了。这是因为L1正则化的损失函数不是连续可导的，而{‘newton-cg’, ‘lbfgs’,‘sag’}这三种优化算法时都需要损失函数的一阶或者二阶连续导数。而‘liblinear’并没有这个依赖。

**dual** : bool, default: False

> Dual or primal formulation. Dual formulation is only implemented for l2 penalty with liblinear solver. Prefer dual=False when n_samples > n_features.

>&emsp;&emsp;对偶或原始方法，bool类型，默认为False。对偶方法只用在求解线性多核(liblinear)的L2惩罚项上。当样本数量>样本特征的时候，dual通常设置为False。

**tol** : float, default: 1e-4

> Tolerance for stopping criteria.

>&emsp;&emsp;收敛准则。停止求解的标准，float类型，默认为1e-4。就是求解到多少的时候，停止，认为已经求出最优解。


**C** : float, default: 1.0

> Inverse of regularization strength; must be a positive float. 正则项（惩罚项）系数的导数。

Like in support vector machines, smaller values specify stronger regularization.

（通SVM中的C，C值越小，表示惩罚程度越大）

>&emsp;&emsp;正则化系数λ的倒数，float类型，默认为1.0。必须是正浮点型数。像SVM一样，越小的数值表示越强的正则化。

**fit_intercept** : bool, default: True

> Specifies if a constant (a.k.a. bias or intercept) should be added to the decision function.

>&emsp;&emsp;是否存在截距或偏差，即确认有没有0次项。

**intercept_scaling** : float, default 1.

> Useful only when the solver ‘liblinear’ is used and self.fit_intercept is set to True. 

仅在正则化项为”liblinear”，且fit_intercept设置为True时有用。float类型，默认为1。

In this case, x becomes [x, self.intercept_scaling], i.e. a “synthetic” feature with constant value equal to intercept_scaling is appended to the instance vector. The intercept becomes `intercept_scaling * synthetic_feature_weight`.

> 

> Note! the synthetic feature weight is subject to l1/l2 regularization as all other features. To lessen the effect of regularization on synthetic feature weight (and therefore on the intercept) intercept_scaling has to be increased.

>&emsp;&emsp;仅在正则化项为”liblinear”，且fit_intercept设置为True时有用。float类型，默认为1。

**class_weight** : dict or ‘balanced’, default: None

> Weights associated with classes in the form `{class_label: weight}`. If not given, all classes are supposed to have weight one.

> 

> The “balanced” mode uses the values of y to automatically adjust weights inversely proportional to class frequencies in the input data as `n_samples / (n_classes * np.bincount(y))`.

> 

> Note that these weights will be multiplied with sample_weight (passed through the fit method) if sample_weight is specified.

> 

> New in version 0.17: *class_weight=’balanced’*

>&emsp;&emsp;用于标示分类模型中各种类型的权重，可以是一个字典或者’balanced’字符串，默认为不输入，也就是不考虑权重，即为None。如果选择输入的话，可以选择balanced让类库自己计算类型权重，或者自己输入各个类型的权重。举个例子，比如对于0,1的二元模型，我们可以定义class_weight={0:0.9,1:0.1}，这样类型0的权重为90%，而类型1的权重为10%。如果class_weight选择balanced，那么类库会根据训练样本量来计算权重。某种类型样本量越多，则权重越低，样本量越少，则权重越高。当class_weight为balanced时，类权重计算方法如下：n_samples / (n_classes * np.bincount(y))。n_samples为样本数，n_classes为类别数量，np.bincount(y)会输出每个类的样本数，例如y=[1,0,0,1,1],则np.bincount(y)=[2,3]。 

>&emsp;&emsp;那么class_weight有什么作用呢？ 

>&emsp;&emsp;在分类模型中，我们经常会遇到两类问题：

>&emsp;&emsp;第一种是误分类的代价很高。比如对合法用户和非法用户进行分类，将非法用户分类为合法用户的代价很高，我们宁愿将合法用户分类为非法用户，这时可以人工再甄别，但是却不愿将非法用户分类为合法用户。这时，我们可以适当提高非法用户的权重。

>&emsp;&emsp;第二种是样本是高度失衡的，比如我们有合法用户和非法用户的二元样本数据10000条，里面合法用户有9995条，非法用户只有5条，如果我们不考虑权重，则我们可以将所有的测试集都预测为合法用户，这样预测准确率理论上有99.95%，但是却没有任何意义。这时，我们可以选择balanced，让类库自动提高非法用户样本的权重。提高了某种分类的权重，相比不考虑权重，会有更多的样本分类划分到高权重的类别，从而可以解决上面两类问题。

**random_state** : int, RandomState instance or None, optional, default: None

> The seed of the pseudo random number generator to use when shuffling the data. If int, random_state is the seed used by the random number generator; If RandomState instance, random_state is the random number generator; If None, the random number generator is the RandomState instance used by <cite style="font-style: normal;">np.random</cite>. Used when `solver` == ‘sag’ or ‘liblinear’.

>&emsp;&emsp;随机数种子，int类型，可选参数，默认为无，仅在正则化优化算法为sag,liblinear时有用。

**solver** : {‘newton-cg’, ‘lbfgs’, ‘liblinear’, ‘sag’, ‘saga’},

> default: ‘liblinear’ Algorithm to use in the optimization problem.

>&emsp;&emsp;优化算法选择参数，只有五个可选参数，即newton-cg,lbfgs,liblinear,sag,saga。默认为liblinear。solver参数决定了我们对逻辑回归损失函数的优化方法，有四种算法可以选择，分别是： 

&emsp;&emsp;liblinear：使用了开源的liblinear库实现，内部使用了坐标轴下降法来迭代优化损失函数。

&emsp;&emsp;lbfgs：拟牛顿法的一种，利用损失函数二阶导数矩阵即海森矩阵来迭代优化损失函数。

&emsp;&emsp;newton-cg：也是牛顿法家族的一种，利用损失函数二阶导数矩阵即海森矩阵来迭代优化损失函数。

&emsp;&emsp;sag：即随机平均梯度下降，是梯度下降法的变种，和普通梯度下降法的区别是每次迭代仅仅用一部分的样本来计算梯度，适合于样本数据多的时候。

&emsp;&emsp;saga：线性收敛的随机优化算法的的变重。

&emsp;&emsp;总结： 

&emsp;&emsp;liblinear适用于小数据集，而sag和saga适用于大数据集因为速度更快。

&emsp;&emsp;对于多分类问题，只有newton-cg,sag,saga和lbfgs能够处理多项损失，而liblinear受限于一对剩余(OvR)。啥意思，就是用liblinear的时候，如果是多分类问题，得先把一种类别作为一个类别，剩余的所有类别作为另外一个类别。一次类推，遍历所有类别，进行分类。

&emsp;&emsp;newton-cg,sag和lbfgs这三种优化算法时都需要损失函数的一阶或者二阶连续导数，因此不能用于没有连续导数的L1正则化，只能用于L2正则化。而liblinear和saga通吃L1正则化和L2正则化。

&emsp;&emsp;同时，sag每次仅仅使用了部分样本进行梯度迭代，所以当样本量少的时候不要选择它，而如果样本量非常大，比如大于10万，sag是第一选择。但是sag不能用于L1正则化，所以当你有大量的样本，又需要L1正则化的话就要自己做取舍了。要么通过对样本采样来降低样本量，要么回到L2正则化。

&emsp;&emsp;从上面的描述，大家可能觉得，既然newton-cg, lbfgs和sag这么多限制，如果不是大样本，我们选择liblinear不就行了嘛！错，因为liblinear也有自己的弱点！我们知道，逻辑回归有二元逻辑回归和多元逻辑回归。对于多元逻辑回归常见的有one-vs-rest(OvR)和many-vs-many(MvM)两种。而MvM一般比OvR分类相对准确一些。郁闷的是liblinear只支持OvR，不支持MvM，这样如果我们需要相对精确的多元逻辑回归时，就不能选择liblinear了。也意味着如果我们需要相对精确的多元逻辑回归不能使用L1正则化了。
 

**max_iter** : int, default: 100

> Useful only for the newton-cg, sag and lbfgs solvers. Maximum number of iterations taken for the solvers to converge.

>&emsp;&emsp;算法收敛最大迭代次数，int类型，默认为100。仅在正则化优化算法为newton-cg, sag和lbfgs才有用，算法收敛的最大迭代次数。

**multi_class** : str, {‘ovr’, ‘multinomial’}, default: ‘ovr’

> Multiclass option can be either ‘ovr’ or ‘multinomial’. If the option chosen is ‘ovr’, then a binary problem is fit for each label. Else the loss minimised is the multinomial loss fit across the entire probability distribution. Does not work for liblinear solver.
> 
> New in version 0.18: Stochastic Average Gradient descent solver for ‘multinomial’ case.

>&emsp;&emsp;分类方式选择参数，str类型，可选参数为ovr和multinomial，默认为ovr。ovr即前面提到的one-vs-rest(OvR)，而multinomial即前面提到的many-vs-many(MvM)。如果是二元逻辑回归，ovr和multinomial并没有任何区别，区别主要在多元逻辑回归上。 

&emsp;&emsp;OvR和MvM有什么不同*？* 

&emsp;&emsp;OvR的思想很简单，无论你是多少元逻辑回归，我们都可以看做二元逻辑回归。具体做法是，对于第K类的分类决策，我们把所有第K类的样本作为正例，除了第K类样本以外的所有样本都作为负例，然后在上面做二元逻辑回归，得到第K类的分类模型。其他类的分类模型获得以此类推。

&emsp;&emsp;而MvM则相对复杂，这里举MvM的特例one-vs-one(OvO)作讲解。如果模型有T类，我们每次在所有的T类样本里面选择两类样本出来，不妨记为T1类和T2类，把所有的输出为T1和T2的样本放在一起，把T1作为正例，T2作为负例，进行二元逻辑回归，得到模型参数。我们一共需要T(T-1)/2次分类。

&emsp;&emsp;可以看出OvR相对简单，但分类效果相对略差（这里指大多数样本分布情况，某些样本分布下OvR可能更好）。而MvM分类相对精确，但是分类速度没有OvR快。如果选择了ovr，则4种损失函数的优化方法liblinear，newton-cg,lbfgs和sag都可以选择。但是如果选择了multinomial,则只能选择newton-cg, lbfgs和sag了。


**verbose** : int, default: 0

> For the liblinear and lbfgs solvers set verbose to any positive number for verbosity.

>&emsp;&emsp;日志冗长度，int类型。默认为0。就是不输出训练过程，1的时候偶尔输出结果，大于1，对于每个子模型都输出。

**warm_start** : bool, default: False

> When set to True, reuse the solution of the previous call to fit as initialization, otherwise, just erase the previous solution. Useless for liblinear solver.
> 
> New in version 0.17: *warm_start* to support *lbfgs*, *newton-cg*, *sag*, *saga* solvers.

>&emsp;&emsp;热启动参数，bool类型。默认为False。如果为True，则下一次训练是以追加树的形式进行（重新使用上一次的调用作为初始化）。

**n_jobs** : int, default: 1

> Number of CPU cores used when parallelizing over classes if multi_class=’ovr’”. This parameter is ignored when the [``](http://sklearn.apachecn.org/cn/0.19.0/modules/generated/sklearn.linear_model.LogisticRegression.html#id1)solver``is set to ‘liblinear’ regardless of whether ‘multi_class’ is specified or not. If given a value of -1, all cores are used.

>&emsp;&emsp;并行数。int类型，默认为1。1的时候，用CPU的一个内核运行程序，2的时候，用CPU的2个内核运行程序。为-1的时候，用所有CPU的内核运行程序。

##### 4.2.2.2 Attributes 属性

- ###### coef_ : 

&emsp;&emsp;array, shape (1, n_features) or (n_classes, n_features)

&emsp;&emsp;Coefficient of the features in the decision function.

&emsp;&emsp;coef_ is of shape (1, n_features) when the given problem is binary.

- ###### intercept_ : array, shape (1,) or (n_classes,)

&emsp;&emsp;Intercept (a.k.a. bias) added to the decision function.

&emsp;&emsp;If fit_intercept is set to False, the intercept is set to zero. intercept_ is of shape(1,) when the problem is binary.

- ###### n_iter_ : 

&emsp;&emsp;array, shape (n_classes,) or (1, )

&emsp;&emsp;Actual number of iterations for all classes. If binary or multinomial, it returns only 1 element. For liblinear solver, only the maximum number of iteration across all classes is given.

#### 3.1.3 Methods 方法

-  [`decision_function`](http://sklearn.apachecn.org/cn/0.19.0/modules/generated/sklearn.linear_model.LogisticRegression.html#sklearn.linear_model.LogisticRegression.decision_function "sklearn.linear_model.LogisticRegression.decision_function")(X) 

Predict confidence scores for samples. 

- [`densify`](http://sklearn.apachecn.org/cn/0.19.0/modules/generated/sklearn.linear_model.LogisticRegression.html#sklearn.linear_model.LogisticRegression.densify "sklearn.linear_model.LogisticRegression.densify")()

Convert coefficient matrix to dense array format. 

- [`fit`](http://sklearn.apachecn.org/cn/0.19.0/modules/generated/sklearn.linear_model.LogisticRegression.html#sklearn.linear_model.LogisticRegression.fit "sklearn.linear_model.LogisticRegression.fit")(X, y[, sample_weight]) 

Fit the model according to the given training data. 

- [`get_params`](http://sklearn.apachecn.org/cn/0.19.0/modules/generated/sklearn.linear_model.LogisticRegression.html#sklearn.linear_model.LogisticRegression.get_params "sklearn.linear_model.LogisticRegression.get_params")([deep]) | Get parameters for this estimator. 

- [`predict`](http://sklearn.apachecn.org/cn/0.19.0/modules/generated/sklearn.linear_model.LogisticRegression.html#sklearn.linear_model.LogisticRegression.predict "sklearn.linear_model.LogisticRegression.predict")(X) 

 Predict class labels for samples in X. 

- [`predict_log_proba`](http://sklearn.apachecn.org/cn/0.19.0/modules/generated/sklearn.linear_model.LogisticRegression.html#sklearn.linear_model.LogisticRegression.predict_log_proba "sklearn.linear_model.LogisticRegression.predict_log_proba")(X) 

Log of probability estimates. 

- [`predict_proba`](http://sklearn.apachecn.org/cn/0.19.0/modules/generated/sklearn.linear_model.LogisticRegression.html#sklearn.linear_model.LogisticRegression.predict_proba "sklearn.linear_model.LogisticRegression.predict_proba")(X)

Probability estimates.

- [`score`](http://sklearn.apachecn.org/cn/0.19.0/modules/generated/sklearn.linear_model.LogisticRegression.html#sklearn.linear_model.LogisticRegression.score "sklearn.linear_model.LogisticRegression.score")(X, y[, sample_weight])

Returns the mean accuracy on the given test data and labels. 

- [`set_params`](http://sklearn.apachecn.org/cn/0.19.0/modules/generated/sklearn.linear_model.LogisticRegression.html#sklearn.linear_model.LogisticRegression.set_params "sklearn.linear_model.LogisticRegression.set_params")(**params)

Set the parameters of this estimator. 

- [`sparsify`](http://sklearn.apachecn.org/cn/0.19.0/modules/generated/sklearn.linear_model.LogisticRegression.html#sklearn.linear_model.LogisticRegression.sparsify "sklearn.linear_model.LogisticRegression.sparsify")() 

Convert coefficient matrix to sparse format. 


##### 4.2.2.3 总结： 

&emsp;&emsp;Logistic回归的目的是寻找一个非线性函数Sigmoid的最佳拟合参数，求解过程可以由最优化算法完成。

&emsp;&emsp;改进的一些最优化算法，比如sag。它可以在新数据到来时就完成参数更新，而不需要重新读取整个数据集来进行批量处理。

&emsp;&emsp;机器学习的一个重要问题就是如何处理缺失数据。这个问题没有标准答案，取决于实际应用中的需求。现有一些解决方案，每种方案都各有优缺点。

&emsp;&emsp;我们需要根据数据的情况，这是Sklearn的参数，以期达到更好的分类效果。


<br>
<br>
<br>
<br>


## Reference:

1.[Logistic Regression 模型简介](https://tech.meituan.com/intro_to_logistic_regression.html)

2.[【机器学习算法系列之二】浅析Logistic Regression](https://chenrudan.github.io/blog/2016/01/09/logisticregression.html)

3.[Machine-Learning-From-Scratch/logistic_regression/logistic_regression.py](https://github.com/RRdmlearning/Machine-Learning-From-Scratch/blob/master/logistic_regression/logistic_regression.py)

4.[【机器学习算法系列之二】浅析Logistic Regression](https://chenrudan.github.io/blog/2016/01/09/logisticregression.html)

5.[Softmax分类函数](https://www.jianshu.com/p/8eb17fa41164)

6.[sklearn实现逻辑回归分类](http://sklearn.apachecn.org/cn/0.19.0/auto_examples/linear_model/plot_iris_logistic.html#sphx-glr-auto-examples-linear-model-plot-iris-logistic-py)

7.[sklearn中LogisticRegression文档](http://sklearn.apachecn.org/cn/0.19.0/modules/generated/sklearn.linear_model.LogisticRegression.html#sklearn.linear_model.LogisticRegression)

8.[scikit-learn 逻辑回归类库使用小结](http://www.cnblogs.com/pinard/p/6035872.html)

9.[LogisticRegression - 参数说明](https://blog.csdn.net/jark_/article/details/78342644)