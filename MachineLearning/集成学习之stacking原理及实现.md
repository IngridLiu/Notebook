# 集成学习之stacking原理及实现

<br>
<br>

## 1. Stacking介绍

&emsp;&emsp;将个体学习器结合在一起的时候使用的方法叫做结合策略。

&emsp;&emsp;对于连续的值使用平均法，对于分类值使用投票法。

&emsp;&emsp;还有一种结合策略是使用另外一个机器学习算法来将个体机器学习器的结果结合在一起，这个方法就是Stacking。

&emsp;&emsp;在stacking方法中，我们把个体学习器叫做初级学习器，用于结合的学习器叫做次级学习器或元学习器（meta-learner）。

&emsp;&emsp;我们贴一张周志华老师《机器学习》一张图来说一下stacking学习算法。

![](https://images2018.cnblogs.com/blog/890640/201803/890640-20180313164917723-1210285777.png)

&emsp;&emsp;过程1-3 是训练出来个体学习器，也就是初级学习器

&emsp;&emsp;过程5-9是 使用训练出来的个体学习器来得预测的结果，这个预测的结果当做次级学习器的训练集

&emsp;&emsp;过程11 是用初级学习器预测的结果训练出次级学习器，得到我们最后训练的模型。

&emsp;&emsp;这个算法还可以有别的情况，那就是过程4，我们其实不用从一个空集开始构造次级训练集，我们可以把预测出来的结果当做一个特征，追加到我们的数据集当中。第三篇参考文章就是用的这个方法。

<br>

## 2.Stacking的实现

&emsp;&emsp;方法一：

&emsp;&emsp;最先想到的方法是这样的，用数据集D来训练h1,h2,h3...，然后再用这些训练出来的初级学习器在数据集D上面进行预测得到次级训练集。 这样的想法是不行的，因为这样容易过拟合。用原始数据训练出来的模型再来预测原始数据，模型的预测情况肯定是非常不错的，但是在新数据上表现并不一定好。
 
&emsp;&emsp;方法二：

&emsp;&emsp;我们使用k折交叉验证的方法来得到次级训练集。将数据D分为k等份：D1,D2,D3....Dk。

&emsp;&emsp;for j = 1,2,...k:  ，我们取数据集 D\Dj 作为训练集来训练模型h1,h2,h3...，然后让模型h1,h2,h3...预测Dj的值，并将这个值保存下来，最后所有保存下来值组成了。

```python
import numpy as np
from sklearn.model_selection import KFold
def get_stacking(clf, x_train, y_train, x_test, n_folds=10):
    """
    这个函数是stacking的核心，使用交叉验证的方法得到次级训练集
    x_train, y_train, x_test 的值应该为numpy里面的数组类型 numpy.ndarray . 
    如果输入为pandas的DataFrame类型则会把报错"""
    train_num, test_num = x_train.shape[0], x_test.shape[0]
    train_set = np.zeros((train_num,))
    test_set = np.zeros((test_num,))
    test_nfolds_sets = np.zeros((test_num, n_folds))
    kf = KFold(n_splits=n_folds)

    for i,(train_index, test_index) in enumerate(kf.split(x_train)):
        x_tra, y_tra = x_train[train_index], y_train[train_index]
        x_tst, y_tst =  x_train[test_index], y_train[test_index]

        clf.fit(x_tra, y_tra)

        train_set[test_index] = clf.predict(x_tst)
        test_nfolds_sets[:,i] = clf.predict(x_test)

    test_set[:] = test_nfolds_sets.mean(axis=1)
    return train_set, test_set



#我们这里使用5个分类算法，为了体现stacking的思想，就不加参数了
from sklearn.ensemble import (RandomForestClassifier, AdaBoostClassifier,
                              GradientBoostingClassifier, ExtraTreesClassifier)
from sklearn.svm import SVC

rf_model = RandomForestClassifier()
adb_model = AdaBoostClassifier()
gdbc_model = GradientBoostingClassifier()
et_model = ExtraTreesClassifier()
svc_model = SVC()

#在这里我们使用train_test_split来人为的制造一些数据
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
iris = load_iris()
train_x, test_x, train_y, test_y = train_test_split(iris.data, iris.target, test_size=0.2)

train_sets = []
test_sets = []
for clf in [rf_model, adb_model, gdbc_model, et_model, svc_model]:
    train_set, test_set = get_stacking(clf, train_x, train_y, test_x)
    train_sets.append(train_set)
    test_sets.append(test_set)

meta_train = np.concatenate([result_set.reshape(-1,1) for result_set in train_sets], axis=1)
meta_test = np.concatenate([y_test_set.reshape(-1,1) for y_test_set in test_sets], axis=1)

#使用决策树作为我们的次级分类器
from sklearn.tree import DecisionTreeClassifier
dt_model = DecisionTreeClassifier()
dt_model.fit(meta_train, train_y)
df_predict = dt_model.predict(meta_test)

print(df_predict)
```

<br>
<br>
<br>
<br>

## Reference:

1.[集成学习之stacking原理及实现](https://hk.saowen.com/a/99a20abed5654ddc407bc58ed88aed57fe66241e1175f4e6e0142662f95bc983)