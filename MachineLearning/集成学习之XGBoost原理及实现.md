# 集成学习之XGBoost原理及实现

<br>
<br>

&emsp;&emsp;XGBoost是boosting算法的其中一种。Boosting算法的思想是将许多弱分类器集成在一起形成一个强分类器。因为XGBoost是一种提升树模型，所以它是将许多树模型集成在一起，形成一个很强的分类器。而所用到的树模型则是CART回归树模型。讲解其原理前，先讲解一下CART回归树。

## 1. XGBoost介绍

&emsp;&emsp;XGBoost是boosting算法的其中一种。Boosting算法的思想是将许多弱分类器集成在一起形成一个强分类器。因为XGBoost是一种提升树模型，所以它是将许多树模型集成在一起，形成一个很强的分类器。而所用到的树模型则是CART回归树模型。讲解其原理前，先讲解一下CART回归树。

### 1.1 CART回归树

&emsp;&emsp;CART回归树是假设树为二叉树，通过不断将特征进行分裂。比如当前树结点是基于第j个特征值进行分裂的，设该特征值小于s的样本划分为左子树，大于s的样本划分为右子树。

![](https://pic1.zhimg.com/80/v2-30cbc85f5fa9412b156e97ac8ae5a9b4_hd.jpg)

&emsp;&emsp;而CART回归树实质上就是在该特征维度对样本空间进行划分，而这种空间划分的优化是一种NP难问题，因此，在决策树模型中是使用启发式方法解决。典型CART回归树产生的目标函数为：

![](https://pic3.zhimg.com/80/v2-376e6ca8712d4c80dccf92ceab1e8b5e_hd.jpg)

&emsp;&emsp;因此，当我们为了求解最优的切分特征j和最优的切分点s，就转化为求解这么一个目标函数：

![](https://pic4.zhimg.com/80/v2-d5f181fb2b237192ef73458d8e256913_hd.jpg)

### 1.2 XGBoost算法思想

&emsp;&emsp;该算法思想就是不断地添加树，不断地进行特征分裂来生长一棵树，每次添加一个树，其实是学习一个新函数，去拟合上次预测的残差。当我们训练完成得到k棵树，我们要预测一个样本的分数，其实就是根据这个样本的特征，在每棵树中会落到对应的一个叶子节点，每个叶子节点就对应一个分数，最后只需要将每棵树对应的分数加起来就是该样本的预测值。

![](https://pic1.zhimg.com/80/v2-500c06febf37f708edaab67978e8d470_hd.jpg)

&emsp;&emsp;注：w_q(x)为叶子节点q的分数，f(x)为其中一棵回归树

&emsp;&emsp;如下图例子，训练出了2棵决策树，小孩的预测分数就是两棵树中小孩所落到的结点的分数相加。爷爷的预测分数同理。

![](https://pic1.zhimg.com/80/v2-d0746433e5d47e7064ebb99646c2157c_hd.jpg)

### 1.3 XGBoost原理

&emsp;&emsp;XGBoost目标函数定义为：

![](https://pic3.zhimg.com/80/v2-9fc4ae8e364d87a1eed872a3089554da_hd.jpg)

&emsp;&emsp;目标函数由两部分构成，第一部分用来衡量预测分数和真实分数的差距，另一部分则是正则化项。正则化项同样包含两部分，T表示叶子结点的个数，w表示叶子节点的分数。γ可以控制叶子结点的个数，λ可以控制叶子节点的分数不会过大，防止过拟合。

&emsp;&emsp;正如上文所说，新生成的树是要拟合上次预测的残差的，即当生成t棵树后，预测分数可以写成：

![](https://pic2.zhimg.com/80/v2-f5cb6db258369715959f7e503d4f6095_hd.jpg)

&emsp;&emsp;同时，可以将目标函数改写成：

![](https://pic1.zhimg.com/80/v2-ac9480b103188ba08ca504d1d5f23368_hd.jpg)

&emsp;&emsp;很明显，我们接下来就是要去找到一个f_t能够最小化目标函数。XGBoost的想法是利用其在f_t=0处的泰勒二阶展开近似它。所以，目标函数近似为：

![](https://pic2.zhimg.com/80/v2-f55328f65607371842efa8e93be034e9_hd.jpg)

&emsp;&emsp;其中g_i为一阶导数，h_i为二阶导数：

![](https://pic3.zhimg.com/80/v2-b21e6c400f47540a3e1a72f1f720372a_hd.jpg)

&emsp;&emsp;由于前t-1棵树的预测分数与y的残差对目标函数优化不影响，可以直接去掉。简化目标函数为：

![](https://pic4.zhimg.com/80/v2-69780a54fb161d8424120fc278231f4b_hd.jpg)

&emsp;&emsp;上式是将每个样本的损失函数值加起来，我们知道，每个样本都最终会落到一个叶子结点中，所以我们可以将所以同一个叶子结点的样本重组起来，过程如下图：

![](https://pic4.zhimg.com/80/v2-26eb9b742a1f906b73ecb9d44afb6a03_hd.jpg)

&emsp;&emsp;因此通过上式的改写，我们可以将目标函数改写成关于叶子结点分数w的一个一元二次函数，求解最优的w和目标函数值就变得很简单了，直接使用顶点公式即可。因此，最优的w和目标函数公式为

![](https://pic1.zhimg.com/80/v2-0b266ae6539e79de88c4e0bcb98228d8_hd.jpg)

### 1.4 分裂结点算法

&emsp;&emsp;在上面的推导中，我们知道了如果我们一棵树的结构确定了，如何求得每个叶子结点的分数。但我们还没介绍如何确定树结构，即每次特征分裂怎么寻找最佳特征，怎么寻找最佳分裂点。

&emsp;&emsp;正如上文说到，基于空间切分去构造一颗决策树是一个NP难问题，我们不可能去遍历所有树结构，因此，XGBoost使用了和CART回归树一样的想法，利用贪婪算法，遍历所有特征的所有特征划分点，不同的是使用上式目标函数值作为评价函数。具体做法就是分裂后的目标函数值比单子叶子节点的目标函数的增益，同时为了限制树生长过深，还加了个阈值，只有当增益大于该阈值才进行分裂。

&emsp;&emsp;同时可以设置树的最大深度、当样本权重和小于设定阈值时停止生长去防止过拟合。

### 1.5 Shrinkage and Column Subsampling

&emsp;&emsp;XGBoost还提出了两种防止过拟合的方法：Shrinkage and Column Subsampling。Shrinkage方法就是在每次迭代中对树的每个叶子结点的分数乘上一个缩减权重η，这可以使得每一棵树的影响力不会太大，留下更大的空间给后面生成的树去优化模型。Column Subsampling类似于随机森林中的选取部分特征进行建树。其可分为两种，一种是按层随机采样，在对同一层内每个结点分裂之前，先随机选择一部分特征，然后只需要遍历这部分的特征，来确定最优的分割点。另一种是随机选择特征，则建树前随机选择一部分特征然后分裂就只遍历这些特征。一般情况下前者效果更好。

### 1.6 近似算法

&emsp;&emsp;对于连续型特征值，当样本数量非常大，该特征取值过多时，遍历所有取值会花费很多时间，且容易过拟合。因此XGBoost思想是对特征进行分桶，即找到l个划分点，将位于相邻分位点之间的样本分在一个桶中。在遍历该特征的时候，只需要遍历各个分位点，从而计算最优划分。从算法伪代码中该流程还可以分为两种，全局的近似是在新生成一棵树之前就对各个特征计算分位点并划分样本，之后在每次分裂过程中都采用近似划分，而局部近似就是在具体的某一次分裂节点的过程中采用近似算法。

![](https://pic2.zhimg.com/80/v2-b85a4ebbbee419393804b1c0af2bae09_hd.jpg)

### 1.7 针对稀疏数据的算法（缺失值处理）

&emsp;&emsp;当样本的第i个特征值缺失时，无法利用该特征进行划分时，XGBoost的想法是将该样本分别划分到左结点和右结点，然后计算其增益，哪个大就划分到哪边。

<br>

## 2.XGBoost实现
```python
# 数据准备
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import Imputer

data = pd.read_csv('../input/train.csv')
data.dropna(axis=0, subset=['SalePrice'], inplace=True)
y = data.SalePrice
X = data.drop(['SalePrice'], axis=1).select_dtypes(exclude=['object'])
train_X, test_X, train_y, test_y = train_test_split(X.as_matrix(), y.as_matrix(), test_size=0.25)

my_imputer = Imputer()
train_X = my_imputer.fit_transform(train_X)
test_X = my_imputer.transform(test_X)

# 训练模型
from xgboost import XGBRegressor

my_model = XGBRegressor()
# Add silent=True to avoid printing out updates with each cycle
my_model.fit(train_X, train_y, verbose=False)


# make predictions
predictions = my_model.predict(test_X)

from sklearn.metrics import mean_absolute_error
print("Mean Absolute Error : " + str(mean_absolute_error(predictions, test_y)))


# tuning model
my_model = XGBRegressor(n_estimators=1000)
my_model.fit(train_X, train_y, early_stopping_rounds=5, 
             eval_set=[(test_X, test_y)], verbose=False)
```


## 3.XGBoost的优点

&emsp;&emsp;之所以XGBoost可以成为机器学习的大杀器，广泛用于数据科学竞赛和工业界，是因为它有许多优点：

&emsp;&emsp;1.使用许多策略去防止过拟合，如：正则化项、Shrinkage and Column Subsampling等。

&emsp;&emsp;2. 目标函数优化利用了损失函数关于待求函数的二阶导数

&emsp;&emsp;3.支持并行化，这是XGBoost的闪光点，虽然树与树之间是串行关系，但是同层级节点可并行。具体的对于某个节点，节点内选择最佳分裂点，候选分裂点计算增益用多线程并行。训练速度快。

&emsp;&emsp;4.添加了对稀疏数据的处理。

&emsp;&emsp;5.交叉验证，early stop，当预测结果已经很好的时候可以提前停止建树，加快训练速度。

&emsp;&emsp;6.支持设置样本权重，该权重体现在一阶导数g和二阶导数h，通过调整权重可以去更加关注一些样本。


<br>
<br>
<br>
<br>

## Reference:

1. [一文读懂机器学习大杀器XGBoost原理](https://zhuanlan.zhihu.com/p/40129825)

2. [XGBoost实现教程](https://www.kaggle.com/dansbecker/xgboost)