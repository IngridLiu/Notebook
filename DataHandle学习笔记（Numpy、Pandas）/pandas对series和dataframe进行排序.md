# pandas 对series和dataframe进行排序

<br>
<br>
<br>

```
#coding=utf-8
import pandas as pd
import numpy as np
#以下实现排序功能。
series=pd.Series([3,4,1,6],index=['b','a','d','c'])
frame=pd.DataFrame([[2,4,1,5],[3,1,4,5],[5,1,4,2]],columns=['b','a','d','c'],index=['one','two','three'])
print frame
print series
print 'series通过索引进行排序：'
print series.sort_index()
print 'series通过值进行排序:'
print series.sort_values()
print 'dataframe根据行索引进行降序排序（排序时默认升序，调节ascending参数）：'
print frame.sort_index(ascending=False)
print 'dataframe根据列索引进行排序：'
print frame.sort_index(axis=1)
print 'dataframe根据值进行排序：'
print frame.sort_values(by='a')
print '通过多个索引进行排序：'
print frame.sort_values(by=['a','c'])

```

实验结果：
       b  a  d  c
one    2  4  1  5
two    3  1  4  5
three  5  1  4  2
b    3
a    4
d    1
c    6
dtype: int64
series通过索引进行排序：
a    4
b    3
c    6
d    1
dtype: int64
series通过值进行排序:
d    1
b    3
a    4
c    6
dtype: int64
dataframe根据行索引进行降序排序（排序时默认升序，调节ascending参数）：
       b  a  d  c
two    3  1  4  5
three  5  1  4  2
one    2  4  1  5
dataframe根据列索引进行排序：
       a  b  c  d
one    4  2  5  1
two    1  3  5  4
three  1  5  2  4
dataframe根据值进行排序：
       b  a  d  c
two    3  1  4  5
three  5  1  4  2
one    2  4  1  5
通过两个索引进行排序：
       b  a  d  c
three  5  1  4  2
two    3  1  4  5
one    2  4  1  5
[Finished in 1.0s]

