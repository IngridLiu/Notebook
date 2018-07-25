# pandas 时间日期处理

<br>
<br>
<br>

&emsp;&emsp;pandas有着强大的日期数据处理功能，本期我们来了解下pandas处理日期数据的一些基本功能，主要包括以下三个方面：

&emsp;&emsp;按日期筛选数据

&emsp;&emsp;按日期显示数据

&emsp;&emsp;按日期统计数据

## 1 读取并整理数据

### 1.1 读取数据

&emsp;&emsp;首先引入pandas库:

```
import pandas as pd

```

&emsp;&emsp;从csv文件中读取数据:

```
df = pd.read_csv('date.csv', header=None)
print(df.head(2))

            0  1
0  2013-10-24  3
1  2013-10-25  4

```

&emsp;&emsp;整理数据:

```
df.columns = ['date','number']
df['date'] = pd.to_datetime(df['date']) #将数据类型转换为日期类型
df = df.set_index('date') # 将date设置为index
print(df.head(2))
print(df.tail(2))
print(df.shape)

            number
date              
2013-10-24       3
2013-10-25       4
            number
date              
2017-02-14       6
2017-02-22       6
(425, 1)

```

&emsp;&emsp;df的行数一共是425行。

&emsp;&emsp;将df的index设为datetime类型：

```
df.index = pd.DatetimeIndex(df.index)

```


### 1.2 查看Dataframe的数据类型

```
print(type(df))
print(df.index)
print(type(df.index))

<class 'pandas.core.frame.DataFrame'>
DatetimeIndex(['2013-10-24', '2013-10-25', '2013-10-29', '2013-10-30',
               '2013-11-04', '2013-11-06', '2013-11-08', '2013-11-12',
               '2013-11-14', '2013-11-25',
               ...
               '2017-01-03', '2017-01-07', '2017-01-14', '2017-01-17',
               '2017-01-23', '2017-01-25', '2017-01-26', '2017-02-07',
               '2017-02-14', '2017-02-22'],
              dtype='datetime64[ns]', name='date', length=425, freq=None)
<class 'pandas.tseries.index.DatetimeIndex'>

```

### 1.3 构造Series类型数据

```
s = pd.Series(df['number'], index=df.index)
print(type(s))
s.head(2)
<class 'pandas.core.series.Series'>

date
2013-10-24    3
2013-10-25    4
Name: number, dtype: int64

```

<br>

## 2 按日期筛选数据

### 2.1 按年度获取数据

```
print('---------获取2013年的数据-----------')
print(df['2013'].head(2)) # 获取2013年的数据
print(df['2013'].tail(2)) # 获取2013年的数据

---------获取2013年的数据-----------
            number
date              
2013-10-24       3
2013-10-25       4
            number
date              
2013-12-27       2
2013-12-30       2

```

### 2.2 获取2016至2017年的数据

```
print('---------获取2016至2017年的数据-----------')
print(df['2016':'2017'].head(2))  #获取2016至2017年的数据
print(df['2016':'2017'].tail(2))  #获取2016至2017年的数据
---------获取2016至2017年的数据-----------
            number
date              
2016-01-04       4
2016-01-07       6
            number
date              
2017-02-14       6
2017-02-22       6
```

### 2.3 获取某月的数据

```
print('---------获取某月的数据-----------')
print(df['2013-11']) # 获取某月的数据
---------获取某月的数据-----------
            number
date              
2013-11-04       1
2013-11-06       3
2013-11-08       1
2013-11-12       5
2013-11-14       2
2013-11-25       1
2013-11-29       1

```

### 2.4 获取具体某天的数据

&emsp;&emsp;请注意dataframe类型的数据，获取具体某天的数据时，跟series是有些差异的，详细情况如下述代码所示：

&emsp;&emsp;按日期筛选数据

```
print('---------获取具体某天的数据-----------')
# 获取具体某天的数据
print(s['2013-11-06'])

# 获取具体某天的数据，用datafrme直接选取某天时会报错，而series的数据就没有问题
# print(df['2013-11-06'])

#可以考虑用区间来获取某天的数据
print(df['2013-11-06':'2013-11-06'])

---------获取具体某天的数据-----------
3
            number
date              
2013-11-06       3
```

&emsp;&emsp;dataframe的truncate函数可以获取某个时期之前或之后的数据，或者某个时间区间的数据

&emsp;&emsp;但一般建议直接用切片（slice），这样更为直观，方便

&emsp;&emsp;但一般建议直接用切片（slice），这样更为直观，方便

```
print('---------获取某个时期之前或之后的数据-----------')
print('--------after------------')
print(df.truncate(after = '2013-11'))
print('--------before------------')
print(df.truncate(before='2017-02'))
---------获取某个时期之前或之后的数据-----------
--------after------------
            number
date              
2013-10-24       3
2013-10-25       4
2013-10-29       2
2013-10-30       1
--------before------------
            number
date              
2017-02-07       8
2017-02-14       6
2017-02-22       6
```

<br>

## 3 按日期显示数据

### 3.1 to_period()方法

&emsp;&emsp;请注意df.index的数据类型是DatetimeIndex；

&emsp;&emsp;df_peirod的数据类型是PeriodIndex

#### 3.1.1 按月显示，但不统计

```
df_period = df.to_period('M') #按月显示，但不统计
print(type(df_period))

print(type(df_period.index))
# 请注意df.index的数据类型是DatetimeIndex；
# df_peirod的数据类型是PeriodIndex

print(df_period.head())
<class 'pandas.core.frame.DataFrame'>
<class 'pandas.tseries.period.PeriodIndex'>
         number
date           
2013-10       3
2013-10       4
2013-10       2
2013-10       1
2013-11       1

```

#### 3.1.2 按季度显示，但不统计

```
print(df.to_period('Q').head()) #按季度显示，但不统计

        number
date          
2013Q4       3
2013Q4       4
2013Q4       2
2013Q4       1
2013Q4       1

```

#### 3.1.3 按年度显示，但不统计

```
print(df.to_period('A').head()) #按年度显示，但不统计

      number
date        
2013       3
2013       4
2013       2
2013       1
2013       1

```





