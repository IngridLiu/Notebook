# datetime：数字日期和时间

## 1 Python 标准库中 time 和 datetime 的区别与联系

&emsp;&emsp;Python 中提供了对时间日期的多种多样的处理方式，主要是在 time 和 datetime 这两个模块里。

### 1.1 time

&emsp;&emsp;在 Python 文档里，time是归类在Generic Operating System Services中，换句话说， 它提供的功能是更加接近于操作系统层面的。通读文档可知，time 模块是围绕着 Unix Timestamp 进行的。

&emsp;&emsp;该模块主要包括一个类 struct_time，另外其他几个函数及相关常量。 需要注意的是在该模块中的大多数函数是调用了所在平台C library的同名函数， 所以要特别注意有些函数是平台相关的，可能会在不同的平台有不同的效果。另外一点是，由于是基于Unix Timestamp，所以其所能表述的日期范围被限定在 1970 - 2038 之间，如果你写的代码需要处理在前面所述范围之外的日期，那可能需要考虑使用datetime模块更好。

### 1.2 datetime

&emsp;&emsp;datetime 比 time 高级了不少，可以理解为 datetime 基于 time 进行了封装，提供了更多实用的函数。在datetime 模块中包含了几个类，具体关系如下:

```
object
    timedelta     # 主要用于计算时间跨度
    tzinfo        # 时区相关
    time          # 只关注时间
    date          # 只关注日期
        datetime  # 同时有时间和日期
```

&emsp;&emsp;名称比较绕口，在实际实用中，用得比较多的是 datetime.datetime 和 datetime.timedelta ，另外两个 datetime.date 和 datetime.time 实际使用和 datetime.datetime 并无太大差别。 下面主要讲讲 datetime.datetime 的使用。使用datetime.datetime.now()可以获得当前时刻的datetime.datetime 实例。 对于一个 datetime.datetime 实例，主要会有以下属性及常用方法，看名称就能理解，应该没有太大问题：

<br>
<br>

## 2 datetime的使用

### 2.1 获取系统时间

```
import datetime

date_time = datetime.datetime.now()

```

### 2.2 datetime对象与日期互转
```
import datetime

data_str = '2016-05-01 12:01:01'

# 字符串转日期
data_time = datetime.datetime.strptime(data_str, '%Y-%m-%d %H:%M:%S')

# 日期转字符串
local_str = data_time.strftime('%Y-%m-%d %H:%M:%S')

```

&emsp;&emsp;还有一点需要注意的是， strptime() 的性能要比你想象中的差很多， 因为它是使用纯Python实现，并且必须处理所有的系统本地设置。 如果你要在代码中需要解析大量的日期并且已经知道了日期字符串的确切格式，可以自己实现一套解析方案来获取更好的性能。 比如，如果你已经知道所以日期格式是 YYYY-MM-DD ，你可以像下面这样实现一个解析函数：

```
from datetime import datetime
def parse_ymd(s):
    year_s, mon_s, day_s = s.split('-')
    return datetime(int(year_s), int(mon_s), int(day_s))
```


<br>
<br>

## 3 datetime比较大小

&emsp;&emsp;datetime 采用与数值变量相同的比较大小的方法。

<br>
<br>

## 4 datetime进行加减处理

```
from dateutil.relativedelta import relativedelta

date_time = datetime.datetime.now()

# 当前时间之后三个月的时间
time_then = date_time + relativedelta(months=+3)


```