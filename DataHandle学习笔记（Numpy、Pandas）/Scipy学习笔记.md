# Scipy学习笔记

<br>
<br>

## Scipy的子任务模块


|模块|模块功能|
|:---|:---|
|scipy.cluster|向量计算 / Kmeans|
|scipy.constants|物理和数学常量|
|scipy.fftpack|傅里叶变换|
|scipy.integrate|积分程序|
|scipy.interpolate|插值|
|scipy.io|数据输入和输出|
|scipy.linalg|线性代数程序|
|scipy.ndimage|n-维图像包|
|scipy.odr|正交距离回归|
|scipy.optimize|优化|
|scipy.signal|信号处理|
|scipy.sparse|稀疏矩阵|
|scipy.spatial|空间数据结构和算法|
|scipy.special|一些特殊数学函数|
|scipy.stats|统计|

导入Numpy和Scipy的标准方式：

```python
import numpy as np
from scipy import stats  # 其他的子模块类似
```

## Scipy文件输入/输出

[scipy.io](https://docs.scipy.org/doc/scipy/reference/io.html#scipy.io)

```python
# 载入和保存matlab文件
from scipy import io as spio
a = np.ones((3, 3))
spio.savemat('file.mat', {'a': a}) # savemat expects a dictionary
data = spio.loadmat('file.mat', struct_as_record=True)
```

<br>

## Scipy线性代数操作

[scipy.linalg](https://docs.scipy.org/doc/scipy/reference/linalg.html#scipy.linalg)

```python
from scipy import linalg

linalg.det(arr)  # 计算矩阵的行列式
linalg.inv(arr)  # 计算方阵的逆方阵
uarr, spec, vharr = linalg.svd(arr) # 奇异值分解（SVD）
```

<br>

## Scipy统计分析

```python
'''
双总体T检验：
Scipy提供了两个方法解决双样本同方差的Student t-test问题： 
'''
scipy.stats.ttest_ind(a, b, axis=0, equal_var=True, nan_policy='propagate')[source]  # Returns:statistic, pvalue;
scipy.stats.ttest_ind_from_stats(mean1, std1, nobs1, mean2, std2, nobs2, equal_var=True)[source] # Returns:statistic, pvalue;
```



## Reference:

1. [scipy.stats.ttest_ind](https://docs.scipy.org/doc/scipy/reference/generated/scipy.stats.ttest_ind.html)

2. [scipy.stats.ttest_ind_from_stats](https://docs.scipy.org/doc/scipy/reference/generated/scipy.stats.ttest_ind_from_stats.html)













