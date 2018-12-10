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
np.array([0, 1, 2, 3, 4])
np.arange(5)
np.arange(15).reshape(3, 5)
a = np.array([[1,2,3],[4,5,6]])
b = np.array([[7,8,9],[10,11,12]])
np.linspace(0, 2*np.pi, 5)

np.zeros(size)  #创建shape为size的元素为0的array,zeros(shape, dtype=float, order='C')
np.ones(size)   #创建shape为size的元素为1的array
np.empty(size)  #创建shape为size的元素为空的array，注意empty创建的数组中，包含的均是无意义的数值。
np.random.uniform(low, high, size)  #从一个均匀分布[low,high)中随机采样，注意定义域是左闭右开，即包含low，不包含high; low: 采样下界，float类型，默认值为0；high: 采样上界，float类型，默认值为1；size: 输出样本数目，为int或元组(tuple)类型，例如，size=(m,n,k), 则输出m*n*k个样本，缺省时输出1个值。

data_np.astype(float)   #np数组类型转换为float

np.matrix(A) # 创建矩阵，Numpy matrices必须是2维的,但是 numpy arrays (ndarrays) 可以是多维的；
np.mat()    # np.mat()同np.matrix()

```

### Numpy数组获取
```python
a[2:5]  # 数据切片
```

### Numpy计算

```python
c = a - b   # array a和b中对应元素相减
c = a * b   # array a和b中对应元素相乘

np.round(A, ndigits) # 对A中每一个元素做四舍五入，碰到精确度(ndigits)为的下一位为5，若精确度位上为基数则进一位，否则舍去；

np.dot(A, B)    # 计算A、B矩阵乘法
A.dot(B)    #同上，计算A、B矩阵相乘
np.multiply(A, B)   # 计算A、B矩阵对应元素相乘，结果同A*B
np.add(A, B)    # 计算A、B矩阵对应元素相加，结果同A+B

np.exp(A)   # 对A中每一个元素做指数计算
np.log(A)   # 对A中每一个元素做log计算
np.sqrt(A)  # 对A中每一个元素做开方计算
np.sign(A)   # 符号函数,对A中每一个元素做sign计算,若元素<0取-1，若元素=0取0，若元素>0取1；

np.max(a, axis = 0) # 取出每一列中的最大的值，返回值为一行;若axis=1，取出每一行中最大的值，返回值为一列；若省略axis参数取出array中的最大值；
np.min()    # 同上
np.inf  # 无穷大

np.floor(x) # np.floor返回每个元素x不大于输入参数x的最大整数。

```

### numpy 数组形状改变
```python
a.ravel()  # returns the array of a， flattened
a.reshape(3, 5) # 改变shape
a.T  # # array A 做转置

# np数组合并
c = np.vstack((a,b))    #数组纵向合并
c = np.r_[a,b]  //数组纵向合并
# array([[1, 2, 3],
#        [4, 5, 6],
#        [1, 1, 1],
#        [2, 2, 2]])
d = np.hstack((a,b))    #数组横向合并
d = np.c_[a,b]  //数组横向合并
c = np.columns_stack((a, b))
# array([[1, 2, 3, 1, 1, 1],
#        [4, 5, 6, 2, 2, 2]])

# 将一个数组分成几个较小的数组
np.hsplit(a, 3) # 划分为3个片段
np.hsplit(a, (3, 4))    # 以第3列和第4列后作为分割间隔点
```

### numpy复制和视图
```python
b = a   # 复制a，b和a相同
c = a.view()    # c是a的视图，属于a，改变c不会改变a
d = a.copy()    # d是a的深拷贝，d、a之间没有任何关系

```

### numpy读取/写入数据
```python
data = np.loadtxt(filepath,delimiter,usecols,unpack)    #numpy从文本中加载数据
```

## Reference:


1. [NumPy 中文文档](https://numpy.org.cn/index.html)

1. [NumPy 中文用户指南](https://numpy.org.cn/user_guide/index.html)

2. [NumPy 中文参考手册](https://numpy.org.cn/reference/index.html)