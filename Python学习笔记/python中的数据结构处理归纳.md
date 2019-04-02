# python中的数据结构处理归纳



### python中的运算符

|运算符|作用|
|:----|:----|
|**|幂乘|
|%|取余|
|//|取整|
|||

变量在使用前必须 “定义”(赋值)，否则会出错。

整数和点数的混合计算中，整数会被转换为浮点数。


### str

```python
3 * 'nu' + 'num' # unununium，字符串可以由+操作符连接在一起，可以由*表示重复。
string[0]  # 字符串也可以被截取(检索)
string[-1] # 索引也可以是负数
string[0:2] # 字符串切片，包含起始的字符，不包含末尾的字符。
string[:4]  # 切片的索引有非常有用的默认值；省略的第一个索引默认为零，省略的第二个索引默认为切片的字符串的大小。
len(string) # 返回字符串长度
```
Python字符串不可以被更改 — 它们是 不可变的 

<br>

### list

```python
list = [[1,2,3],[4,5,6]]
b = [[1,1,1],[2,2,2]]

list[0]    # list可以被索引
list[-1]   # list索引可以是复数
list[0:2]  # list被切片
list[0] = [1, 3, 4]    # list可改变，可修改元素
list[0:1] = [[1,1,1],[2,2,2]]
list+b    # [[1, 2, 3], [4, 5, 6], [1, 1, 1], [2, 2, 2]],list合并
list.append(b[0])  # list使用append()函数在末尾添加新的元素
list.extend(b) # [[1, 2, 3], [4, 5, 6], [1, 1, 1], [2, 2, 2]]，list合并
list.insert(i, x)   # 在list中索引i的位置插入元素x
list.remove(x)  # 去除list中的元素x
list.pop(i) # 去除list中索引i位置的元素，若i省略，则去除最后一个位置上的元素
list.clear()    # 清楚list中的元素
list.index(x)   # 返回list中元素x的索引
list.count(x)   # 返回list中元素x出现的次数
list.sort(key=None, reverse=False)  # 对list中的项目进行排序
list.reverse()  # 反转列表中的元素, reverse()函数返回为空
list.copy() # list的浅拷贝

len(list)  # 返回list a 的长度
del list[0] # del声明删除list中元素

new_list = [x.append(3) for x in list]
```

### tuple元组

元组由多个值组成，这些值由逗号分隔。

```python
tuple = ([1, 2, 3],)
tuple = 'hello'
len(tuple)  # 1

```

### sets集合

sets是没有重复元素的无序集合。

```python
set_1 = set('hello')    # {'h', 'e', 'l', 'l', 'o'}
set_1 - set_2   # 返回在set_1但是不在set_2中的元素
set_1 | set_2   # 返回在set_1或者在set_2中的元素
set_1 & set_2   # 返回在set_1且在set_2中的元素
set_1 ^ set_2   # 返回只在set_1和set_2中只出现一次的元素

```

### dict字典

```python
dic = {x: x**2 for x in [1 ,2 ,3]}

# dic sort
dic = {'a': 2, 'c': 3, 'b': 1}
print(dic.items())
new_dic = sorted(dic.items(), key=lambda x:x[0], reverse = True)  # 按第0个元素降序排列
new_dic = sorted(dic.items(), key=lambda x:x[0], reverse = False) # 按第0个元素升序排列
new_dic = sorted(dic.items(), key=lambda x:x[1], reverse = True)  # 按第1个元素降序排列
new_dic = sorted(dic.items(), key=lambda x:x[1], reverse = False) # 按第1个元素升序排列
```

### datetime：数字日期和时间

```python
import datetime

date_time = datetime.datetime.now() #获取系统时间
data_str = '2016-05-01 12:01:01'    #字符串日期

data_time = datetime.datetime.strptime(data_str, '%Y-%m-%d %H:%M:%S')   #字符串转日期
local_str = data_time.strftime('%Y-%m-%d %H:%M:%S') #日期转字符串

time_then = date_time + timedelta(days=1)   #获取当前时间的之后一天
time_then = date_time + timedelta(months=1)   #获取当前时间的之后一个月的一天
```

### python中编码格式的转换

```python
# 转换字符串的编码
unicodestring = u"Hello world"  # 直接定义unicode字符串，通过在字符串前加 u 的方式
utf8string = '好人'  #可以这样直接写，是因为在py文件的开头写了 #encoding=utf-8, 这样在整个py文件中，所有的字符串的编码编码方式都设置为了utf-8

ustring = unicode(utf8string, "utf-8")  # 将某种字符集编码的字符串转化为unicode字符串， 即“解码”

unicodestring.encode("utf-8")   #将unicode字符串转化为某种字符集编码的字符串，即“编码”

# 转换list or tuple的编码
list = [unicode(x, 'utf-8') for x in list]

```

### 小数点精度的控制

```python
# 将精度高的浮点数转换成精度低的浮点数。

# 使用内置函数round()
round(2.675)    #   3, round()如果只有一个数作为参数，不指定位数的时候，返回的是一个整数，而且是最靠近的整数（这点上类似四舍五入）。
round(2.5)  #   2, 当出现.5的时候，两边的距离都一样，round()取靠近的偶数，这就是为什么round(2.5) = 2。
round(1.5)  #   2, 碰到.5的这样情况，如果要取舍的位数前的小树是奇数，则直接舍弃，如果偶数这向上取舍。
round(2.675, 2) #   2.67
round(2.665, 2) #   2.67

# 使用格式化
("%.2f" % 2.635)    #   '2.63'
("%.2f" % 2.645)    #   '2.65'

ceil(2.5)   # 3, ceil(x)取大于或者等于x的最小整数。
floor(2.5)  # 2, floor(x)取小于或者等于x的最大整数。
```

## Reference:

1. [谈谈关于Python里面小数点精度控制的问题](https://www.cnblogs.com/herbert/p/3402245.html)

