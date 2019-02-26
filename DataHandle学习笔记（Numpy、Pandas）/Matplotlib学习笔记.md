# Matplotlib学习笔记

<br>
<br>

### Matplotlib入门

```python
import numpy as np
import matplotlib.pyplot as plt
plt.figure()    # 定义一个图像窗口
plt.axhline(y=0, xmin = 0, xmax = 0, linestyle='--', color='gray')    # 添加水平线，
plt.plot(x, y, color = 'red', linewidth = 1.0, linestyle = '--')  # 画(x, y)曲线
plt.xlim((-1, 2))   # 设置x坐标轴范围（-1， 2）
plt.ylim((-2, 3))   # 设置y坐标轴范围（-2， 3）
plt.xlabel('I am x')
plt.ylabel('I am y')
new_ticks = np.linspace(-1, 2, 5)
plt.xticks(new_ticks)
plt.yticks([-2, -1.8, -1, 1.22, 3],[r'$really\ bad$', r'$bad$', r'$normal$', r'$good$', r'$really\ good$'])
plt.show()  # 显示图像
```

# Matplotlib多合一显示
```python
plt.subplot(2, 2, 1)    # 使用plt.subplot来创建小图. plt.subplot(2,2,1)表示将整个图像窗口分为2行2列, 当前位置为1。plt.subplot(2,2,1)可以简写成plt.subplot(221), matplotlib同样可以识别. 
plt.plot([0,1],[0,1])   # 使用plt.plot([0,1],[0,1])在第1个位置创建一个小图.
plt.layout(pad = None, w_pad = None, h_pad = None)    # 自动显示多个子图,参数设定参数图像边界和子图之间的额外边距。边距以字体大小单位规定。
```

### 设定子图属性
```python
ax = plt.subplots()
ax.set_title(u'title')   # 设定图标title

ax.set_ylim([y_min, y_max]) # 设定纵坐标范围
ax.set_ylabel(u'y_label')   # 设定纵坐标轴标签

ax.set_xlabel(u'x_label')   # 设定横坐标标签
ax.set_xticks(ind)  # 设定横坐标刻度
ax.set_xticklabels(x_labels)    # 设定横坐标刻度上标签
```


<br>
<br>

## Reference:

1. [Matplotlib画图教程系列](https://morvanzhou.github.io/tutorials/data-manipulation/plt/)

2. []()