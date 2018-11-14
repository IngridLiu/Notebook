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

```
import numpy as np

# 数组创建
a = np.array([0, 1, 2, 3, 4])
c = np.arange(5)
d = np.linspace(0, 2*np.pi, 5)
data = np.loadtxt(filepath,delimiter,usecols,unpack)    #numpy从文本中加载数据

a = np.array([[1,2,3],[4,5,6]])
b = np.array([[1,1,1],[2,2,2]]）

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

data_np.astype(float)   #np数组类型转换为float

np.dot(A, B)    # 计算A、B矩阵乘法
np.multiply(A, B)   # 计算A、B矩阵对应元素相乘，结果同A*B

```


## Reference:


1. [NumPy 中文文档](https://numpy.org.cn/index.html)

1. [NumPy 中文用户指南](https://numpy.org.cn/user_guide/index.html)

2. [NumPy 中文参考手册](https://numpy.org.cn/reference/index.html)