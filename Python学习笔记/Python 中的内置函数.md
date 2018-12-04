# Python中的内置函数

<br>
<br>

### lambda函数

&emsp;&emsp;lambda函数有如下特性：

&emsp;&emsp;lambda函数是匿名的：所谓匿名函数，通俗地说就是没有名字的函数。lambda函数没有名字。

&emsp;&emsp;lambda函数有输入和输出：输入是传入到参数列表argument_list的值，输出是根据表达式expression计算得到的值。

&emsp;&emsp;lambda函数一般功能简单：单行expression决定了lambda函数不可能完成复杂的逻辑，只能完成非常简单的功能。由于其实现的功能一目了然，甚至不需要专门的名字来说明。

&emsp;&emsp;示例：

```python
ks1 = [1,2,3,4,5,6,7,8,9]
ku = lambda x: x+1, ks1
print(ku)
# 结果为 [2, 3, 4, 5, 6, 7, 8, 9, 10]：
```

### eval()函数

&emsp;&emsp;eval() 函数用来执行一个字符串表达式，并返回表达式的值。

&emsp;&emsp;以下是 eval() 方法的语法:

```
eval(expression[, globals[, locals]])
# 参数
# - expression -- 表达式。
# - globals -- 变量作用域，全局命名空间，如果被提供，则必须是一个字典对象。
# - locals -- 变量作用域，局部命名空间，如果被提供，可以是任何映射对象。
```

&emsp;&emsp;实例：

```
>>>x = 7
>>> eval( '3 * x' )
21
>>> eval('pow(2,2)')
4
```

### python中的assert

python assert断言是声明其布尔值必须为真的判定，如果发生异常就说明表达示为假。可以理解assert断言语句为raise-if-not，用来测试表示式，其返回值为假，就会触发异常。

示例：

```python
assert len(['my boy',12])<10
assert range(4)==[0,1,2,3]
```

assert的异常参数，其实就是在断言表达式后添加字符串信息，用来解释断言并更好的知道是哪里出了问题。格式如下：

assert expression [, arguments]

assert 表达式 [, 参数]

```python
assert len(lists) >=5,'列表元素个数小于5'
assert 2==1,'2不等于1'
```

### python中使用future

Python提供了__future__模块，把下一个新版本的特性导入到当前版本，于是我们就可以在当前版本中测试一些新版本的特性。

示例：

如果你想在Python 2.7的代码中直接使用Python 3.x的除法，可以通过__future__模块的division实现：

```python
from __future__ import division

print '10 / 3 =', 10 / 3
print '10.0 / 3 =', 10.0 / 3
print '10 // 3 =', 10 // 3

# 结果如下：
# 10 / 3 = 3.33333333333
# 10.0 / 3 = 3.33333333333
# 10 // 3 = 3
```


## Reference:

1. [python assert的作用](http://www.cnblogs.com/liuchunxiao83/p/5298016.html)

1. [使用__future__](https://www.liaoxuefeng.com/wiki/001374738125095c955c1e6d8bb493182103fac9270762a000/001386820023084e5263fe54fde4e4e8616597058cc4ba1000)