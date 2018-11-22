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
df.index    # 显示df的index
df.columns  # 显示df的columns
df.values   # 显示df中的值
df.head(n)  # 显示数据的前n行
df.tail(n)  # 显示数据的最后n行

# df排序
frame.sort_index(axis=1, ascending=False) # dataframe根据列索引(axis = 0 或者省略时表示根据行索引)进行降序排序（排序时默认升序，调节ascending参数）
frame.sort_values(by='a') # dataframe根据值进行排序
frame.sort_values(by=['a','c'])   # 通过多个索引进行排序

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

# pandas dataframe数据获取与计算
```python
df.T    # df的转置

df['A'] # df中A列的数据
df[0:3] # 切片，获取0、1、2行的数据
df['20130102':'20130104']   #切片，在index为date类型的情况下，获取20130102-20130104（包含20140104）的行的所有数据

df.loc['20130102':'20130104', ['A', 'B']]   # 获取20130102-20130104行，A、B列的数据
df.at['20130102', 'A'] # 结果同df.loc['20130102', 'A']，返回一个标量

# 通过位置选择
df.iloc[3:5, 0:2]   # 根据位置对数据切片
df.iloc[[1,2,4], [0,2]] # 根据位置获取对应位置数据
df.iloc[1:3, :] # 对行进行切片
df.iloc[:, 1:3] # 对列进行切片

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
```


# pandas 时间日期处理

```python
# 创建datetime类型数据
df.columns = ['date','number']
df['date'] = pd.to_datetime(df['date']) # 将数据类型转换为日期类型
df.index = pd.DatetimeIndex(df.index)   # 将df的index设为datetime类型

# 数据获取
df['2016':'2017']   # 获取2016至2017年的数据
df['2013-11']   # 获取某月的数据
df['2013-11-06':'2013-11-06']   #获取具体某天的数据，获取具体某天的数据，用datafrme直接选取某天时会报错，而series的数据就没有问题，可以考虑用区间来获取某天的数据。
# dataframe的truncate函数可以获取某个时期之前或之后的数据，或者某个时间区间的数据，但一般建议直接用切片（slice），这样更为直观，方便。
df.truncate(after = '2013-11')  # 获取某个时期之后的数据
df.truncate(before='2017-02')   # 获取某个时期之前的数据

# 按年、月、日显示数据，但不统计
df.to_period('M')   # 按月显示，但不统计；请注意df.index的数据类型是DatetimeIndex，df_peirod的数据类型是PeriodIndex
df.to_period('Q')   # 按季度显示，但不统计
df.to_period('A')   #按年度显示，但不统计

```




## Reference：

1. [十分钟搞定Pandas](http://docs.bdpt.net/docs/pandastutorialcn/en/latest/10.html)

1. [Pandas秘籍](http://docs.bdpt.net/docs/pandastutorialcn/en/latest/21.html)

2. [Pandas新手入门教程](http://docs.bdpt.net/docs/pandastutorialcn/en/latest/31.html)