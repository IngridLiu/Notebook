# Pandas归纳

<br>
<br>

<br>
<br>
<br>
<br>

### DataFrame基本操作

```python
#dataframe创建
s4 = pd.Series({"name": "nick", "age": 12, "sex": "male"})  # 通过dic创建Serise
 
d2 = pd.DataFrame(data=list([[1, 2, 3, 4], ["a", "b", "c", "d"]]))  # 通过list创建DataFrame
d3 = pd.DataFrame(data={"name": "nick", "age": 12, "sex": "male"}, index=list([1, 2, 3]))
d4 = pd.DataFrame(data={"A":{"name": "nick", "age": 12, "sex": "male"},"B":{"name": "nick", "age": 12, "sex": "male"}})
d5 = pd.DataFrame(data=s4)

# 指定dataframe数据类型
df = pd.DataFrame(a, dtype='float') #将所有数据设为同一类型
df = pd.DataFrame(a, columns = cols, dtype = {'col_name':str})  #对DataFrame中不同列设置不同的dtype

# 查看df信息
df.shape    # 显示df的shape信息
df.index    # 显示df的index
df.columns  # 显示df的columns
df.values   # 显示df中的值
df.head(n)  # 显示数据的前n行
df.tail(n)  # 显示数据的最后n行

# df排序
df.sort_index(axis=1, ascending=False) # dataframe根据列索引(axis = 0 或者省略时表示根据行索引)进行降序排序（排序时默认升序，调节ascending参数）
df.sort_values(by='a') # dataframe根据值进行排序
df.sort_values(by=['a','c'])   # 通过多个索引进行排序
# df 按指定的list排序, 指定的list所包含元素和Dataframe中需要排序的列的元素一样多
order_list = ['d', 'c', 'b','a','e']
df['A'] = df['A'].astype('category')
df['A'].cat.reorder_categories(order_list, inplace = True)  # inplace = True，使 recorder_categories生效
df.sort_values('A', inplace = True)
# df 按指定的list排序, 指定的list所包含元素比Dataframe中需要排序的列的元素多
# 将上面的df.cat.reorder_categories() 改为df.cat.set_categories()
df['A'].cat.set_categories(list_custom_new, inplace = True)
# df 按指定的list排序, 指定的list所包含元素比Dataframe中需要排序的列的元素少
# 仍旧使用df.cat.set_categories()，order_list中不包含的元素记为0；
df['A'].cat.set_categories(list_custom_new, inplace = True)



# df合并merge
pd.concat[[df1, df2, df3]]  # concat合并多个行
pd.merge(df1, df2, on='key')    # concat合并多个行
df.append(seris, ingore_index = True)   # 在df下添加一行

# df 改变形状

```

### pandas dataframe数据获取
```python
df.T    # df的转置

# 通过标签选择
df['A'] # df中A列的数据
df['20130102':'20130104']   #切片，在index为date类型的情况下，获取20130102-20130104（包含20140104）的行的所有数据
df.loc['20130102':'20130104', ['A', 'B']]   # 获取20130102-20130104行，A、B列的数据

# 通过位置选择
df.iloc[3:5, 0:2]   # 根据位置对数据切片
df.iloc[[1,2,4], [0,2]] # 根据位置获取对应位置数据
df.iloc[1:3, :] # 对行进行切片
df.iloc[:, 1:3] # 对列进行切片
df.iloc[1, 1]   # 获取特定位置的值

# 通过位置与标签选择
df.at['20130102', 'A'] # 结果同df.loc['20130102', 'A']，返回一个标量

# 数据过滤
df[df.A > 0]    # 使用一个单独的列值来过滤，输出df中A列值>0的所有行
df[df > 0]  # 使用where过滤，显示出df中>0的值，未>0的值为空(NaN)
df[df.A.isin(['two', 'four'])]  # 使用isin()方法过滤，选择满足条件的值

# 设置新的值
s1 = pd.Series([1, 2, 3, 4, 5, 6], index = pd.date_range('20130102', periods=6))
df['F'] = s1    # 设置新的列
df.at[dates[0], 'A']    # 通过标签设置新的值
df.iat[0, 1]    # 通过位置舍得新的值
df.loc[:, 'D'] = np.array([5] * len(df))    # 通过一个numpy数组设置一组新值
df[df > 0] = -df    # 通过where操作设置新的值

# 缺失值处理
df.dropna(how = 'any')  # 去掉包含缺失值的行
df.fillna(value = 5)    # 对缺失值进行补充
pd.isnull(df)   # 对数据进行布尔填充
```

### pandas dataframe数据计算
```python
# df设置小数点精度
df.round(2) # 设置df中小数点精度为2
df.round({'A': 1, 'C': 2})  # 设置df中A列小数点精度为1，C列中小数点精度为2

# df将小数转换为百分数
df['A'] = df['A'].apply(lambda x: format(x, '.2%')) # 将df中的A列的小数形式转换为百分数，注意此时A的类型为str

# 计算
df.mean()   # 对df的每一列求平均,默认为axis = 0
df.mean(1)  # 对df的每一行求平均
df.sub()
df.apply(np.cumsum)
df.apply(lambda x: x.max() - x.min())

series.value_counts()   #  形同word count，计算series中每个数的个数
series.str.lower()  # series对象在其str属性中配备了一组字符串处理方法，可以很容易的应用到数组中的每一个元素；

# grouping
df.groupby('A').sum()   # 按列A的数值求和
df.groupby(['A,B']).sum()   # 按列A、B的多层索引求和

# groupby与apply算法结合使用
# 获取每个元素在group中占比
def f(df):
    total = df['count'].sum()
    df['rate_sid'] = df['count'] / total
    return df

data_sid_groupby = total_data_df.groupby(['dim', 'period', 'sid']).apply(f)

# stacked
stacked = df.stack()
stacked.unstack(1)

# 生成透视表
pd.pivot_table(df, values='D', index=['A', 'B'], columns = ['C'])

```




### DataFrame的遍历

```python
# 遍历dataframe中的行
# 方法一
for index, row in df.iterrows():
    print row["c1"], row["c2"]  
# 方法二
for row in df.itertuples(index=True, name='Pandas'):
# 方法三
for i in range(0, len(df)):
    print df.iloc[i]['c1'], df.iloc[i]['c2']
    
# 遍历dataframe中的列
for ix, col in df.iteritems():
    print()

```



### DataFrame列与索引之间的相互转化

```python
# 列转化为索引：
df.set_index('c1')  # 将c1列作为索引
df.set_index(['c1', 'c2'])  #指定c1、c2列作为多级索引，其中c1列为一级索引
df.set_index(['c1', 'c2'], drop=False)  #同时保留作为索引的列

# 索引转化为列
df.reset_index('index1', )    #将index1索引作为列
df.reset_index()    #将df中的多级索引转换为列
df.reset_index('index1', drop = True)   #直接删除索引index1
df.reset_index(inplace=True)    # 直接将原dataframe对象df中索引转为列

# 设置多层索引
index = pd.MultiIndex.from_tuples(tuples, names=['first', 'second'])
df = pd.DataFrame(np.random.randn(8, 2), index, columns=['A', 'B'])



```


# pandas 时间日期处理

```python
# 转换string类型为日期类型数据
df.columns = ['date','number']
df['date'] = pd.to_datetime(df['date']) # 将数据类型转换为日期类型
df.index = pd.DatetimeIndex(df.index)   # 将df的index设为datetime类型


# 数据获取
df['2016':'2017']   # 获取2016至2017年的数据
df['2013-11']   # 获取某月的数据
df['2013-11-06':'2013-11-06']   #获取具体某天的数据，获取具体某天的数据，用datafrme直接选取某天时会报错，而series的数据就没有问题，可以考虑用区间来获取某天的数据。
# dataframe的truncate函数可以获取某个时期之前或之后的数据，或者某个时间区间的数据，但一般建议直接用切片（slice），这样更为直观，方便。
series.truncate(after = '2013-11')  # 获取某个时期之后的数据
series.truncate(before='2017-02')   # 获取某个时期之前的数据
df.index.weekday    # 只获取weekday数据

# 按年、月、日显示数据，但不统计
series.to_period('M')   # 按月显示，但不统计；请注意df.index的数据类型是DatetimeIndex，df_peirod的数据类型是PeriodIndex
series.to_period('Q')   # 按季度显示，但不统计
series.to_period('A')   # 按年度显示，但不统计
series.to_timestamp()   # 转换为时间戳

# 日期数据统计
df.groupby('weekday').aggregate(sum)    # 按星期统计数据和

# 创建时间段
date_range_ind = pd.date_range('1/1/2012', periods=100, freq='S')    # 创建20120101 00：00：00后的100个时期的日期，时期单位为秒；date可以换书写形式；类型为DateIndex
date_series = pd.Series(np.random.randint(0, 500, len(rng)), index = rng)   #以date_range_ind　为index，随机赋值
date_series.resample('5Min').sum() # 计算date_series前5min的数的和

# 时区表示
date_series_utc = date_series.tz_localize('UTC')    #  转换为UTC时区时间
date_series_utc.tz_convert('US/Eastern')    # 转换为时区时间

```

### pandas 读取/存储数据：
```python
# df读取/写入csv
df = pd.read_csv(data_path, sep = '\t', header = None)  # pandas.read_csv(filepath_or_buffer, sep=', ', delimiter=None, header='infer', names=None, index_col=None, usecols=None, squeeze=False, prefix=None, mangle_dupe_cols=True, dtype=None, engine=None, converters=None, true_values=None, false_values=None, skipinitialspace=False, skiprows=None, nrows=None, na_values=None, keep_default_na=True, na_filter=True, verbose=False, skip_blank_lines=True, parse_dates=False, infer_datetime_format=False, keep_date_col=False, date_parser=None, dayfirst=False, iterator=False, chunksize=None, compression='infer', thousands=None, decimal=b'.', lineterminator=None, quotechar='"', quoting=0, escapechar=None, comment=None, encoding=None, dialect=None, tupleize_cols=None, error_bad_lines=True, warn_bad_lines=True, skipfooter=0, doublequote=True, delim_whitespace=False, low_memory=True, memory_map=False, float_precision=None)
df.to_csv(save_path, encoding = 'gb2312')

# df读取/写入hdf5
df = pd.read_hdf('foo.h5', 'df')
df.to_hdf(save_path, 'df')

# df读取/写入excel文件
df = pd.read_excel(data_path, 'sheet', index_col = None, na_values = ['NA'])
df.to_excel(save_path, sheet_name = 'sheet')

```

### pandas Categorical类型数据
```python
# 将A列数据转为category类型
df['A'] = df['A'].astype('category')    


# df 按指定的list排序
# df 按指定的list排序, 指定的list所包含元素和Dataframe中需要排序的列的元素一样多
order_list = ['d', 'c', 'b','a','e']
df['A'] = df['A'].astype('category')
df['A'].cat.reorder_categories(order_list, inplace = True)  # inplace = True，使 recorder_categories生效
df.sort_values('A', inplace = True)
# df 按指定的list排序, 指定的list所包含元素比Dataframe中需要排序的列的元素多
# 将上面的df.cat.reorder_categories() 改为df.cat.set_categories()
df['A'].cat.set_categories(list_custom_new, inplace = True)
# df 按指定的list排序, 指定的list所包含元素比Dataframe中需要排序的列的元素少
# 仍旧使用df.cat.set_categories()，order_list中不包含的元素记为0；
df['A'].cat.set_categories(list_custom_new, inplace = True)

```



## Reference：

1. [十分钟搞定Pandas](http://docs.bdpt.net/docs/pandastutorialcn/en/latest/10.html)

2. [Pandas秘籍](http://docs.bdpt.net/docs/pandastutorialcn/en/latest/21.html)

3. [Pandas新手入门教程](http://docs.bdpt.net/docs/pandastutorialcn/en/latest/31.html)

4. [pandas.read_csv()](https://pandas.pydata.org/pandas-docs/stable/generated/pandas.read_csv.html)

5. [Python： Pandas的DataFrame如何按指定list排序](https://www.cnblogs.com/lemonbit/p/7004505.html)

6. [Pandas Data Visualisation](https://www.kaggle.com/learn/data-visualisation)