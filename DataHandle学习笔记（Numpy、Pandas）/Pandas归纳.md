# Pandas归纳

<br>
<br>

### DataFrame遍历

按行遍历DataFrame：

```python
# iterrows
for index, row in df.iterrows():
    print row["c1"],row["c2"]

# iloc
for i in range(len(df)):
    print df.iloc[i]['c1'],df.iloc[i]['c2']
```

### 转换DataFrame列的类型

```python
# 如果是创建一个DataFrame，可以直接通过dtype参数指定类型
df = pd.DataFrame(a, dtype='float') #将所有数据设为同一类型
df = pd.DataFrame(a, columns = cols, dtype = {'col_name':str})  #对DataFrame中不同列设置不同的dtype

```

### DataFrame列与索引之间的相互转化

列转化为索引：

```python
df.set_index('c1')  # 将c1列作为索引
df.set_index(['c1', 'c2'])  #指定c1、c2列作为多级索引，其中c1列为一级索引
df.set_index(['c1', 'c2'], drop=False)  #同时保留作为索引的列
```

索引转化为列
```python
df.reset_index('index1', )    #将index1索引作为列
df.reset_index()    #将df中的多级索引转换为列
df.reset_index('index1', drop = True)   #直接删除索引index1
df.reset_index(inplace=True)    # 直接将原dataframe对象df中索引转为列


```