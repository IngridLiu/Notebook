# 集成学习之AdaBoost原理及实现

## 1. AdaBoost介绍

AdaBoost，是英文"Adaptive Boosting"（自适应增强）的缩写，是一种机器学习方法，由Yoav Freund和Robert Schapire提出。

AdaBoost方法的自适应在于：前一个分类器分错的样本会被用来训练下一个分类器。AdaBoost方法对于噪声数据和异常数据很敏感。但在一些问题中，AdaBoost方法相对于大多数其它学习算法而言，不会很容易出现过拟合现象。AdaBoost方法中使用的分类器可能很弱（比如出现很大错误率），但只要它的分类效果比随机好一点（比如两类问题分类错误率略小于0.5），就能够改善最终得到的模型。而错误率高于随机分类器的弱分类器也是有用的，因为在最终得到的多个分类器的线性组合中，可以给它们赋予负系数，同样也能提升分类效果。

AdaBoost方法是一种迭代算法，在每一轮中加入一个新的弱分类器，直到达到某个预定的足够小的错误率。每一个训练样本都被赋予一个权重，表明它被某个分类器选入训练集的概率。如果某个样本点已经被准确地分类，那么在构造下一个训练集中，它被选中的概率就被降低；相反，如果某个样本点没有被准确地分类，那么它的权重就得到提高。通过这样的方式，AdaBoost方法能“聚焦于”那些较难分（更富信息）的样本上。

在具体实现上，最初令每个样本的权重都相等，对于第k次迭代操作，我们就根据这些权重来选取样本点，进而训练分类器Ck。然后就根据这个分类器，来提高被它分错的的样本的权重，并降低被正确分类的样本权重。然后，权重更新过的样本集被用于训练下一个分类器Ck。整个训练过程如此迭代地进行下去。

<br>

## 2. AdaBoost详细算法

这里有几个地方的计算需要注意，一个是分类误差率的计算，一个是分类器系数的计算，还有就是权重向量的更新计算。 

![](https://upload-images.jianshu.io/upload_images/10947003-a382659f05c31eba.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/10947003-dc742924ccede5d7.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

<br>

## 3. AdaBoost的向前分步算法解释

前向分步算法是学习加法模型的算法。他的思路是，每一步在前一步的基础上，最小化经验风险，学习该步的基函数和系数。具体到AdaBoost算法就是：**AdaBoost是模型是加法模型，学习算法是前向分步算法，损失函数是指数损失函数**。 

损失函数：

![](https://upload-images.jianshu.io/upload_images/10947003-18284c537cc8f985.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

因为损失函数是指数损失函数，所以上式变成: 

![](https://upload-images.jianshu.io/upload_images/10947003-ba7ca8f1e6839c85.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/10947003-a56ad4d7f01a98b0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/10947003-0380e3d4e3d7b63d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/10947003-41722d85b3705eef.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

<br>

## 4.AdaBoost实现

### 4.1 AdaBoost python实现
```python
# refer: [集成学习Adaboost算法及python实现及sklearn包的调用](https://blog.csdn.net/changzoe/article/details/78921624)
import numpy as np
import matplotlib.pyplot as plt


#  准备数据集
def load_data():
    data_mat = np.matrix([[ 1. ,  2.1],
                        [ 2. ,  1.1],
                        [ 1.3,  1. ],
                        [ 1. ,  1. ],
                        [ 2. ,  1. ]])
    labels = [1.0, 1.0, -1.0, -1.0, 1.0]
    return data_mat, labels

# 画数据集的示意图
def show_scatter(matrix, labels):
    plt.figure(figsize=(8, 6))
    x1 = []
    y1 = []
    x2 = []
    y2 = []
    for i in range(len(labels)):
        if labels[i] == 1.0:
            x1.append(matrix[i, 0])
            y1.append(matrix[i, 1])
        else:
            x2.append(matrix[i, 0])
            y2.append(matrix[i, 1])
    plt.scatter(x1, y1, marker='o',color='g', alpha=0.7, label='1.0')
    plt.scatter(x2, y2, marker='^', color='red', alpha=0.7, label='-1.0')
    plt.title('dataset')
    plt.ylabel('variable Y')
    plt.xlabel('Variable X')
    plt.legend(loc='upper right')
    plt.show()



# 通过阈值比较对数据进行分类的，所有在阈值一边的数据分到类别-1，而在另一边的数据分到类别1
def stump_classify(data_matrix, dimen, thresh_val, thresh_ineq):
    '''
    :param data_matrix: 要分类的数据
    :param dimen: 维度
    :param thresh_val: 阈值
    :param thresh_ineq: 有两种，‘lt’=lower than，‘gt’=greater than
    :return:
    '''
    ret_array = np.ones((np.shape(data_matrix)[0], 1))
    if thresh_ineq == 'lt':
        ret_array[data_matrix[:, dimen] <= thresh_val] = -1.0
    else:
        ret_array[data_matrix[:, dimen] > thresh_val] = -1.0
    return ret_array

# 单层决策树算法的实现
'''
单层决策树生成函数

伪代码：

    将最小错误率minError设为Inf(正无穷)
    对于数据集的每一个特征：（第一层） 
        对每个补步长：（第二层） 
            对每个不等号：（第三层） 
                建立一颗决策树并用加权数据集对它进行测试 
                如果错误率低于minError,将当前决策树设为最佳单层决策树
    返回最佳单层决策树

'''
def build_stump(data_arr, labels, W):
    '''
    :param data_arr:
    :param labels:
    :param D:
    :return:
    '''
    data_matrix = np.mat(data_arr)
    label_mat = np.mat(labels).T
    m,n = np.shape(data_matrix)
    num_steps = 10.0    # num_steps: 用于在特征的所有可能值上遍历
    best_stump = {} # 存储给定权重向量时所得到的最佳单层决策树的相关信息
    best_clas_est = np.mat(np.zeros((m,1))) # 最佳单层决策树的判断
    min_error = np.inf     #np.inf表示无穷大

    for i in range(n):
        # loop over all dimensions
        range_min = data_matrix[:, i].min()
        range_max = data_matrix[:, i].max()
        step_size = (range_max - range_min) / num_steps
        for j in range(-1, int(num_steps)+1):
            # loop over all range in current dimension
            for inequal in ['lt', 'gt']:
                # go over less than and greater than
                thresh_val = (range_min + float(j) * step_size)
                predict_vals = stump_classify(data_matrix, i, thresh_val, inequal)  # call stum classify woth i, j lessthan
                err_arr = np.mat(np.ones((m, 1)))
                err_arr[predict_vals == label_mat] = 0
                weighted_error = W.T * err_arr  # cal total error multiplied by W
                print("split:dim %d, thresh %.2f, thresh inequal: %s, the weighted error is %.3f" % (i, thresh_val, inequal, weighted_error))

                if weighted_error < min_error:
                    min_error = weighted_error
                    best_clas_est = predict_vals.copy()
                    best_stump['dim'] = i
                    best_stump['thresh'] = thresh_val
                    best_stump['ineq'] = inequal
    return best_stump, min_error, best_clas_est

# adaboost 算法的实现
'''
伪代码：

    对每次迭代： 
        利用buildStump()函数找到最佳的单层决策树 
        将最佳单层决策树加入到单层决策树组 
        计算alpha 
        计算新的权重向量D 
        更新累计类别估计值 
        如果错误率大于0.0，退出循环
'''
def adaboost_train_ds(data_arr, labels, num_it = 40):
    weak_class_arr = []
    m = np.shape(data_arr)[0]
    W = np.mat(np.ones((m, 1))/m)   # init W to all equal
    agg_class_est = np.mat(np.zeros((m, 1)))
    for i in range(num_it):
        best_stump , error, class_est = build_stump(data_arr, labels, W)    # build stump
        print("W:", W.T)
        alpha = float(0.5 * np.log((1.0 - error)/max(error, 1e-16)))    # calc alpha, throw in max(error,eps) to account for error=0
        best_stump['alpha'] = alpha
        weak_class_arr.append(best_stump)   #store Stump Params in Array
        print ("classEst: ", class_est.T)
        expon = np.multiply(-1 * alpha * np.mat(labels).T, class_est)  # exponent for D calc, getting messy
        W = np.multiply(W, np.exp(expon)) #  #Calc New W for next iteration
        W = W/W.sum()
        # calc training error of all classifiers, if this is 0 quit for loop early (use break)
        agg_class_est += alpha*class_est
        print("agg_class_est", agg_class_est.T)
        agg_errors = np.multiply(np.sign(agg_class_est) != np.mat(labels).T, np.ones((m, 1)))
        error_rate = agg_errors.sum() / m
        # print ("total error: ",errorRate)
        if error_rate == 0.0: break
    return weak_class_arr, agg_class_est

# 基于adaboost分类
def ada_classify(data_to_class,classifier_arr):
    '''
    :param data_to_class: 待分类的样例
    :param classifier_arr: 弱分类器组成的数组
    :return:
    '''
    data_matrix = np.mat(data_to_class)#do stuff similar to last aggClassEst in adaBoostTrainDS
    m = np.shape(data_matrix)[0]
    agg_class_est = np.mat(np.zeros((m,1)))
    for i in range(len(classifier_arr)):
        class_est = stump_classify(data_matrix,classifier_arr[i]['dim'], classifier_arr[i]['thresh'], classifier_arr[i]['ineq'])#call stump classify
        agg_class_est += classifier_arr[i]['alpha'] * class_est
        #print (agg_class_est)
    return np.sign(agg_class_est)



if __name__ == "__main__":
    data_mat, labels = load_data()
    show_scatter(data_mat, labels)

    W = np.mat(np.ones((5, 1))/5)
    build_stump(data_mat, labels, W)
    classifier_array = adaboost_train_ds(data_mat, labels, 9)
    y_predict = ada_classify(data_mat, classifier_array)
```

### 4.2 sklearn包中有关AdaBoost使用

sklearn 实现代码:

```python
# -*- encoding:utf-8 -*-

'''
本例是Sklearn网站上的关于决策树桩、决策树、
和分别使用AdaBoost—SAMME和AdaBoost—SAMME.R的AdaBoost算法
在分类上的错误率。
这个例子基于Sklearn.datasets里面的make_Hastie_10_2数据库。
取了12000个数据，其他前10000个作为训练集，后面2000个作为了测试集。
'''

import numpy as np
import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import zero_one_loss
from sklearn.ensemble import AdaBoostClassifier
import time
a=time.time()

n_estimators=400
learning_rate=1.0
X,y=datasets.make_hastie_10_2(n_samples=12000,random_state=1)
X_test,y_test=X[10000:],y[10000:]
X_train,y_train=X[:2000],y[:2000]

#决策树桩
dt_stump=DecisionTreeClassifier(max_depth=1,min_samples_leaf=1)
dt_stump.fit(X_train,y_train)
dt_stump_err=1.0-dt_stump.score(X_test,y_test)

#决策树
dt=DecisionTreeClassifier(max_depth=9,min_samples_leaf=1)
dt.fit(X_train,y_train)
dt_err=1.0-dt.score(X_train,y_test)

#决策树桩的生成
ada_discrete=AdaBoostClassifier(base_estimator=dt_stump,learning_rate=learning_rate,
                                n_estimators=n_estimators,algorithm='SAMME')
ada_discrete.fit(X_train,y_train)


ada_real=AdaBoostClassifier(base_estimator=dt_stump,learning_rate=learning_rate,
                                n_estimators=n_estimators,algorithm='SAMME.R')#相比于ada_discrete只改变了Algorithm参数
ada_real.fit(X_train,y_train)

fig=plt.figure()
ax=fig.add_subplot(111)
ax.plot([1,n_estimators],[dt_stump_err]*2,'k-',label='Decision Stump Error')
ax.plot([1,n_estimators],[dt_err]*2,'k--',label='Decision Tree Error')

ada_discrete_err=np.zeros((n_estimators,))
for i,y_pred in enumerate(ada_discrete.staged_predict(X_test)):
    ada_discrete_err[i]=zero_one_loss(y_pred,y_test)#0-1损失，类似于指示函数
ada_discrete_err_train=np.zeros((n_estimators,))
for i,y_pred in enumerate(ada_discrete.staged_predict(X_train)):
    ada_discrete_err_train[i]=zero_one_loss(y_pred,y_train)

ada_real_err=np.zeros((n_estimators,))
for i,y_pred in enumerate(ada_real.staged_predict(X_test)):
    ada_real_err[i]=zero_one_loss(y_pred,y_test)
ada_real_err_train=np.zeros((n_estimators,))
for i,y_pred in enumerate(ada_real.staged_predict(X_train)):
    ada_discrete_err_train[i]=zero_one_loss(y_pred,y_train)


ax.plot(np.arange(n_estimators)+1,ada_discrete_err,label='Discrete AdaBoost Test Error',color='red')
ax.plot(np.arange(n_estimators)+1,ada_discrete_err_train,label='Discrete AdaBoost Train Error',color='blue')
ax.plot(np.arange(n_estimators)+1,ada_real_err,label='Real AdaBoost Test Error',color='orange')
ax.plot(np.arange(n_estimators)+1,ada_real_err_train,label='Real AdaBoost Train Error',color='green')


ax.set_ylim((0.0,0.5))
ax.set_xlabel('n_estimators')
ax.set_ylabel('error rate')


leg=ax.legend(loc='upper right',fancybox=True)
leg.get_frame().set_alpha(0.7)
b=time.time()
print ('total running time of this example is :',(b-a))
plt.show()
```

说明：

常用的组合:

> BaggingClassifier： Bagging分类器组合
> BaggingRegressor： Bagging回归器组合
> AdaBoostClassifier： AdaBoost分类器组合
> AdaBoostRegressor： AdaBoost回归器组合
> GradientBoostingClassifier：GradientBoosting分类器组合
> GradientBoostingRegressor： GradientBoosting回归器组合
> ExtraTreeClassifier：ExtraTree分类器组合
> ExtraTreeRegressor： ExtraTree回归器组合
> RandomTreeClassifier：随机森林分类器组合
> RandomTreeRegressor： 随机森林回归器组合

使用类：

> class sklearn.ensemble.AdaBoostClassifier(base_estimator=None, n_estimators=50,learning_rate=1.0, algorithm='SAMME.R', random_state=None)

> 参数介绍：

>  - base_estimator :(default=DecisionTreeClassifier)
>    选择哪种若分类器，scikit-learn中的分类器都可以
>    我们常用的一般是CART决策树或者神经网络MLP。默认是决策树，即AdaBoostClassifier默认使用CART分类树DecisionTreeClassifier，而AdaBoostRegressor默认使用CART回归树DecisionTreeRegressor

>  - n_estimators :integer, (default=50)
   最大迭代次数，一般来说n_estimators太小，容易欠拟合，n_estimators太大，又容易过拟合，一般选择一个适中的数值。默认是50。在实际调参的过程中，我们常常将n_estimators和下面介绍的参数learning_rate一起考虑。

>  - learning_rate :float, (default=1.0) 迭代次数的每个弱分类器权重设置参数

>  - algorithm : {‘SAMME’, ‘SAMME.R’},(default=’SAMME.R’)
   ’SAMME.R’的话弱分类器需要支持概率预测，比如逻辑回归；‘SAMME’这个是针对离散的变量。


类中方法：
fit(X, y[, sample_weight]) #拟合模型
predict(X)                 #求预测值
predict_proba(X)
score(X, y[, sample_weight])  

> class sklearn.ensemble.AdaBoostRegressor(base_estimator=None, n_estimators=50,learning_rate=1.0, loss='linear', random_state=None)

> 参数：

>  - loss：这个参数只有AdaBoostRegressor有，Adaboost.R2算法需要用到。有线性‘linear’,平方‘square’和指数 ‘exponential’三种选择,默认是线性，一般使用线性就足够了，除非你怀疑这个参数导致拟合度不好。这个值的意义在原理篇我们也讲到了，它对应了我们对第k个弱分类器的中第i个样本的误差的处理，即：如果是线性误差，eki=|yi−Gk(xi)|Ekeki=|yi−Gk(xi)|Ek；如果是平方误差，则eki=(yi−Gk(xi))2E2keki(yi−Gk(xi))2Ek2，如果是指数误差，则eki=1−exp（−yi+Gk(xi))Ek）eki=1−exp（−yi+Gk(xi))Ek），EkEk为训练集上的最大误差Ek=max|yi−Gk(xi)|i=1,2...mEk=max|yi−Gk(xi)|i=1,2...m

>  - base_estimator :(default=DecisionTreeClassifier)
>    选择哪种若分类器，scikit-learn中的分类器都可以
>    我们常用的一般是CART决策树或者神经网络MLP。默认是决策树，即AdaBoostClassifier默认使用CART分类树DecisionTreeClassifier，而AdaBoostRegressor默认使用CART回归树DecisionTreeRegressor

> - learning_rate :float, (default=1.0) 迭代次数的每个弱分类器权重设置参数

>  - n_estimators :integer, (default=50)
>    最大迭代次数，一般来说n_estimators太小，容易欠拟合，n_estimators太大，又容易过拟合，一般选择一个适中的数值。默认是50。在实际调参的过程中，我们常常将n_estimators和下面介绍的参数learning_rate一起考虑

DecisionTreeClassifier和DecisionTreeRegressor的参数重要的如下：

> 1) 划分时考虑的最大特征数max_features: 可以使用很多种类型的值，默认是"None",意味着划分时考虑所有的特征数；如果是"log2"意味着划分时最多考虑log2Nlog2N个特征；如果是"sqrt"或者"auto"意味着划分时最多考虑N−−√N个特征。如果是整数，代表考虑的特征绝对数。如果是浮点数，代表考虑特征百分比，即考虑（百分比xN）取整后的特征数。其中N为样本总特征数。一般来说，如果样本特征数不多，比如小于50，我们用默认的"None"就可以了，如果特征数非常多，我们可以灵活使用刚才描述的其他取值来控制划分时考虑的最大特征数，以控制决策树的生成时间。

> 2) 决策树最大深max_depth: 默认可以不输入，如果不输入的话，决策树在建立子树的时候不会限制子树的深度。一般来说，数据少或者特征少的时候可以不管这个值。如果模型样本量多，特征也多的情况下，推荐限制这个最大深度，具体的取值取决于数据的分布。常用的可以取值10-100之间。

> 3) 内部节点再划分所需最小样本数min_samples_split: 这个值限制了子树继续划分的条件，如果某节点的样本数少于min_samples_split，则不会继续再尝试选择最优特征来进行划分。 默认是2.如果样本量不大，不需要管这个值。如果样本量数量级非常大，则推荐增大这个值。

> 4) 叶子节点最少样本数min_samples_leaf: 这个值限制了叶子节点最少的样本数，如果某叶子节点数目小于样本数，则会和兄弟节点一起被剪枝。 默认是1,可以输入最少的样本数的整数，或者最少样本数占样本总数的百分比。如果样本量不大，不需要管这个值。如果样本量数量级非常大，则推荐增大这个值。

> 5）叶子节点最小的样本权重和min_weight_fraction_leaf：这个值限制了叶子节点所有样本权重和的最小值，如果小于这个值，则会和兄弟节点一起被剪枝。 默认是0，就是不考虑权重问题。一般来说，如果我们有较多样本有缺失值，或者分类树样本的分布类别偏差很大，就会引入样本权重，这时我们就要注意这个值了。

> 6) 最大叶子节点数max_leaf_nodes: 通过限制最大叶子节点数，可以防止过拟合，默认是''None''，即不限制最大的叶子节点数。如果加了限制，算法会建立在最大叶子节点数内最优的决策树。如果特征不多，可以不考虑这个值，但是如果特征分成多的话，可以加以限制，具体的值可以通过交叉验证得到。



<br>
<br>
<br>
<br>





## Reference：

1. [机器学习笔记（十一）AdaBoosting算法](https://www.zybuluo.com/gump88/note/453214)

2. [集成学习Adaboost算法及python实现及sklearn包的调用](https://blog.csdn.net/changzoe/article/details/78921624)