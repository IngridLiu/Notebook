# python中的数据结构处理归纳



### 小数点精度的控制

```
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

### list

```python
a = [[1,2,3],[4,5,6]]
b = [[1,1,1],[2,2,2]]
 
a+b    #[[1, 2, 3], [4, 5, 6], [1, 1, 1], [2, 2, 2]],list合并
a.extend(b) #[[1, 2, 3], [4, 5, 6], [1, 1, 1], [2, 2, 2]]，list合并
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

## Reference:

1. [谈谈关于Python里面小数点精度控制的问题](https://www.cnblogs.com/herbert/p/3402245.html)

