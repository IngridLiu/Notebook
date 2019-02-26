# Statsmodels学习笔记

<br>

## 1. Introduction

&emsp;&emsp;Statsmodels 是 Python 中一个强大的统计分析包，包含了回归分析、时间序列分析、假设检验等等的功能。Statsmodels 在计量的简便性上是远远不及 Stata 等软件的，但它的优点在于可以与 Python 的其他的任务（如 NumPy、Pandas）有效结合，提高工作效率。在本文中，我们重点介绍最回归分析中最常用的 OLS（ordinary least square）功能。

```python
import statsmodels.api as sm
```


## Errors

### 1. AttributeError: 'RangeIndex' object has no attribute 'inferred_freq'

原因：seasonal_decompose() expects a DateTimeIndex on your DataFrame. 

示例解决：

```python
ts_log.index = pd.DatetimeIndex(freq='w', start=0, periods = 1460)
```