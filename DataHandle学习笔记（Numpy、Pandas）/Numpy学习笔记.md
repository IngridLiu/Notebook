# Numpy入门

<br>
<br>
<br>
<br>

&emsp;&emsp;NumPy 是一个运行速度非常快的数学库，主要用于数组计算。它可以让你在 Python 中使用向量和数学矩阵，以及许多用 C 语言实现的底层函数，你还可以体验到从未在原生 Python 上体验过的运行速度。

&emsp;&emsp;NumPy 是 Python 在科学计算领域取得成功的关键之一，如果你想通过 Python 学习数据科学或者机器学习，就必须学习 NumPy。

<br>
<br>

### numpy基础

```python
import numpy as np

# 数组创建及初始化
data = np.loadtxt(filepath,delimiter,usecols,unpack)    #numpy从文本中加载数据
np.array([0, 1, 2, 3, 4])
a = np.array([[1,2,3],[4,5,6]])
b = np.array([[7,8,9],[10,11,12]])
np.arange(5)
np.linspace(0, 2*np.pi, 5)
np.zeros(size)  #创建shape为size的元素为0的array
np.ones(size)   #创建shape为size的元素为1的array
np.empty(size)  #创建shape为size的元素为空的array，注意empty创建的数组中，包含的均是无意义的数值。
np.random.uniform(low, high, size)  #从一个均匀分布[low,high)中随机采样，注意定义域是左闭右开，即包含low，不包含high; low: 采样下界，float类型，默认值为0；high: 采样上界，float类型，默认值为1；size: 输出样本数目，为int或元组(tuple)类型，例如，size=(m,n,k), 则输出m*n*k个样本，缺省时输出1个值。

data_np.astype(float)   #np数组类型转换为float

np.max(a, axis = 0) # 取出每一列中的最大的值，返回值为一行;若axis=1，取出每一行中最大的值，返回值为一列；若省略axis参数取出array中的最大值；
np.min()    # 同上


# np数组合并
c = np.vstack((a,b))    #数组纵向合并
c = np.r_[a,b]  //数组纵向合并
# array([[1, 2, 3],
#        [4, 5, 6],
#        [1, 1, 1],
#        [2, 2, 2]])
d = np.hstack((a,b))    #数组横向合并
d = np.c_[a,b]  //数组横向合并
# array([[1, 2, 3, 1, 1, 1],
#        [4, 5, 6, 2, 2, 2]])



```

### Numpy计算

```python
A.T # array A 做转置

np.round(A, ndigits) # 对A中每一个元素做四舍五入，碰到精确度(ndigits)为的下一位为5，若精确度位上为基数则进一位，否则舍去；

np.dot(A, B)    # 计算A、B矩阵乘法
A.dot(B)    #同上，计算A、B矩阵相乘

np.multiply(A, B)   # 计算A、B矩阵对应元素相乘，结果同A*B

np.exp(A)   #对A中每一个元素做指数计算

```

## Reference:


1. [NumPy 中文文档](https://numpy.org.cn/index.html)

1. [NumPy 中文用户指南](https://numpy.org.cn/user_guide/index.html)

2. [NumPy 中文参考手册](https://numpy.org.cn/reference/index.html)