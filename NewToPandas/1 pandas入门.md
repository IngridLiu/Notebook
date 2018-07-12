# pandas 入门

## 1 pandas 介绍

&emsp;&emsp;Pandas是一个开放源码的Python库，它使用强大的数据结构提供高性能的数据操作和分析工具。它的名字：Pandas是从Panel Data - 多维数据的计量经济学(an Econometrics from Multidimensional data)。

&emsp;&emsp;2008年，为满足需要高性能，灵活的数据分析工具，开发商Wes McKinney开始开发Pandas。

&emsp;&emsp;在Pandas之前，Python主要用于数据迁移和准备。它对数据分析的贡献更小。 Pandas解决了这个问题。 使用Pandas可以完成数据处理和分析的五个典型步骤，而不管数据的来源 - 加载，准备，操作，模型和分析。

&emsp;&emsp;Python Pandas用于广泛的领域，包括金融，经济，统计，分析等学术和商业领域。

&emsp;&emsp;Pandas的主要特点

&emsp;&emsp;快速高效的DataFrame对象，具有默认和自定义的索引。
&emsp;&emsp;将数据从不同文件格式加载到内存中的数据对象的工具。
&emsp;&emsp;丢失数据的数据对齐和综合处理。
&emsp;&emsp;重组和摆动日期集。
&emsp;&emsp;基于标签的切片，索引和大数据集的子集。
&emsp;&emsp;可以删除或插入来自数据结构的列。
&emsp;&emsp;按数据分组进行聚合和转换。
&emsp;&emsp;高性能合并和数据加入。
&emsp;&emsp;时间序列功能。

<br>

## 2 创建dataframe

### 2.1 利用集合创建dataframe

```
d1 = pd.DataFrame(data=list([1, 2, 3]), index=list(["a", "b", "c"]))
print(d1)
```

### 2.2 利用数组创建dataframe

```
d2 = pd.DataFrame(data=numpy.array(list([1, 2, 3, 4, 5, 6, 7])))
print(d2)

```

### 2.3 利用字典创建dataframe

```
dictionary3 = {"name": "nick", "age": 12, "sex": "male"}
d3 = pd.DataFrame(data=dictionary3, index=list([1, 2, 3]))
print(d3)

```

### 2.4 利用series创建dataframe

```
dictionary4 = {"name": "nick", "age": 12, "sex": "male"}
s4 = pd.Series(data=dictionary4)
d4 = pd.DataFrame(data=s4)
print(d4)

```

### 2.5 利用嵌套字典创建dataframe

```
dictionary5 = {"A":{"name": "nick", "age": 12, "sex": "male"},"B":{"name": "nick", "age": 12, "sex": "male"}}
s5 = pd.DataFrame(data=dictionary5)
print(s5)

```

### 2.6 利用嵌套集合创建dataframe

```
s6 = pd.DataFrame(data=list([[1, 2, 3, 4], ["a", "b", "c", "d"]]))
print(s6)

```

### 2.7 利用嵌套数组创建dataframe

```
s7 = pd.DataFrame(data=numpy.array(list([[1, 2, 3, 4], ["a", "b", "c", "d"]])))
print(s7)

```

### 2.8 利用字典创建dataframe

```
s8 = pd.DataFrame.from_dict(
    data={"name": "nick", "age": 12, "sex": "male"}, orient="index")

print(s8)

```

