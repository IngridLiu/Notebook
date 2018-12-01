# Mac上Matplotlib中文乱码问题解决

<br>
<br>

### 第一步: 下载相应的中文字体，并解压：

我喜欢雅黑，下载了微软雅黑字体，喜欢雅黑的可以去我的百度网盘下载：链接:https://pan.baidu.com/s/1d5DdYrlDqFkBMC_Knn1PGg 密码:gypj

### 第二步: 将字体放入matplotlib安装路径下：

1. 找到你matplotlib的安装路径

进入python：
```bash
>>> import matplotlib as mpl
>>> mpl.matplotlib_fname()
/System/Library/Frameworks/Python.framework/Versions/2.7/Extras/lib/python/matplotlib/mpl-data/matplotlibrc
```

2. 打开该目录(shift+command+G)

![](https://pic3.zhimg.com/80/v2-00da4277b52d5c0d8f369eca5ca54b4e_hd.jpg)

![](https://pic4.zhimg.com/80/v2-df7170e539cfa2a261e00fcd7517d42f_hd.jpg)

打开fonts目录,把你的下载后解压的字体文件拷贝到fonts/ttf目录下

![](https://pic2.zhimg.com/80/v2-3f98f75ff422bdf2f3d26d5a47f0dbfd_hd.jpg)

### 第三步：编辑/System/Library/Frameworks/Python.framework/Versions/2.7/Extras/lib/python/matplotlib/mpl-data/matplotlibrc

找到如下片段：

```bash
# 10 pt is the standard value.
#
#font.family         : sans-serif
#font.style          : normal
#font.variant        : normal
#font.weight         : medium
#font.stretch        : normal
...
#font.sans-serif : DejaVu Sans, Bitstream Vera Sans, Lucida Grande, Verdana, Geneva, Lucid, Arial, Helvetica, Avant Garde, sans-serif,Microsoft YaHei
```

font.family前面的#号删除;

font.sans-serif前面的#号删除, 并在:冒号后面加上Microsoft YaHei;

### 第四步：删除 ~/.matplotlib目录

### 第五步：重启IDE工具，第一次使用Matplotlib的时候会重建~/.matplotlib目录下所有内容。

### 第六步：设置代码：

在代码中加入：

```python
import matplotlib as mpl

mpl.rcParams['font.family']='sans-serif'
mpl.rcParams['font.sans-serif']=[u'Microsoft YaHei']
mpl.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号
```

### 注意：

matplotlib中采用unicode编码，字符串采用 u'ingr' 的形式表示为unicode编码方式，若数据产生其它报错可参考下面代码进行修改：

```python
#!/usr/bin/python
# -*-coding:utf-8 -*-

import sys
reload(sys)
sys.setdefaultencoding('utf-8')

import matplotlib as mpl

mpl.rcParams['font.family']='sans-serif'
mpl.rcParams['font.sans-serif']=[u'Microsoft YaHei']
mpl.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号
```



<br>
<br>
<br>
<br>

## Reference:

1. [MacOS下解决Matplotlib中文乱码问题](https://zhuanlan.zhihu.com/p/35085285)