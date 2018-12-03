# TensorFlow学习笔记.md

<br>
<br>


## 1. TensorFlow基本使用

&emsp;&emsp;在TensorFlow中：

&emsp;&emsp;- 使用图（graph）来表示计算任务；

&emsp;&emsp;- 在被称之为会话（Session）的上下文（context）中执行图；

&emsp;&emsp;- 使用tensor表示数据；

&emsp;&emsp;- 通过变量（Variable）维护状态；

&emsp;&emsp;- 使用feed和fetch可以为任意的操作（arbitrary operation）赋值或者从其中获取数据；

&emsp;&emsp;TensorFlow 是一个编程系统, 使用图来表示计算任务. 图中的节点被称之为 op (operation 的缩写). 一个 op 获得 0 个或多个 Tensor, 执行计算, 产生 0 个或多个 Tensor. 每个 Tensor 是一个类型化的多维数组. 例如, 你可以将一小组图像集表示为一个四维浮点数数组, 这四个维度分别是 [batch, height, width, channels].

一个 TensorFlow 图描述了计算的过程. 为了进行计算, 图必须在 会话 里被启动. 会话 将图的 op 分发到诸如 CPU 或 GPU 之类的 设备 上, 同时提供执行 op 的方法. 这些方法执行后, 将产生的 tensor 返回. 在 Python 语言中, 返回的 tensor 是 numpy ndarray 对象; 

### 1.1 图

#### 1.1.1 计算图

&emsp;&emsp;TensorFlow 程序通常被组织成一个构建阶段和一个执行阶段. 在构建阶段, op 的执行步骤 被描述成一个图. 在执行阶段, 使用会话执行执行图中的 op.

&emsp;&emsp;例如, 通常在构建阶段创建一个图来表示和训练神经网络, 然后在执行阶段反复执行图中的训练 op.

#### 1.1.2 构建图

&emsp;&emsp;构建图的第一步, 是创建源 op (source op). 源 op 不需要任何输入, 例如 常量 (Constant). 源 op 的输出被传递给其它 op 做运算.

&emsp;&emsp;Python 库中, op 构造器的返回值代表被构造出的 op 的输出, 这些返回值可以传递给其它 op 构造器作为输入.

```python
import tensorflow as tf

# 创建一个常量 op,产生一个1x2矩阵，这个被作为一个节点
# 加到默认图中
#
# 构造器的返回值代表该常量op的返回值
matrix1 = tf.constant([[3., 3.]])

# 创建另外一个常量op，产生一个2x1矩阵
matrix2 = tf.constant([[2.][2.]])

# 创建一个矩阵乘法 matmul op, 把 'matrix1'和'matrix2'作为输入
# 返回值 'product'代表矩阵乘法的结果
product = tf.matmul(matrix1, matrix2)
```

&emsp;&emsp;默认图现在有三个节点，两个constant() op,和一个matmul() op。为了真正进行矩阵相乘运算, 并得到矩阵乘法的 结果, 你必须在会话里启动这个图.

#### 1.1.3 在一个会话中启动图

&emsp;&emsp;构造阶段完成后, 才能启动图. 启动图的第一步是创建一个 Session 对象, 如果无任何创建参数, 会话构造器将启动默认图.

```python
# 创建session对象，启动默认图
sess = tf.Session()

# 调用sess的'run()'方法来执行矩阵乘法，传入'product'作为该方法的参数
# 上面提到, 'product' 代表了矩阵乘法 op 的输出, 传入它是向方法表明, 我们希望取回矩阵乘法 op 的输出.
# 整个执行过程是自动化的, 会话负责传递 op 所需的全部输入. op 通常是并发执行的.
# 函数调用 'run(product)' 触发了图中三个 op (两个常量 op 和一个矩阵乘法 op) 的执行.
# 返回值 'result' 是一个 numpy `ndarray` 对象.
result = sess.run(product)
print result
# ==> [[12.]]

# 任务完成，关闭会话
sess.close()
```

&emsp;&emsp;Session 对象在使用完后需要关闭以释放资源. 除了显式调用 close 外, 也可以使用 "with" 代码块 来自动完成关闭动作.

```python
with tf.Session() as sess:
  result = sess.run([product])
  print result
```

&emsp;&emsp;在实现上, TensorFlow 将图形定义转换成分布式执行的操作, 以充分利用可用的计算资源(如 CPU 或 GPU). 一般你不需要显式指定使用 CPU 还是 GPU, TensorFlow 能自动检测. 如果检测到 GPU, TensorFlow 会尽可能地利用找到的第一个 GPU 来执行操作.

&emsp;&emsp;如果机器上有超过一个可用的 GPU, 除第一个外的其它 GPU 默认是不参与计算的. 为了让 TensorFlow 使用这些 GPU, 你必须将 op 明确指派给它们执行. with...Device 语句用来指派特定的 CPU 或 GPU 执行操作:

```python
with tf.Session() as sess:
  with tf.device("/gpu:1"):
    matrix1 = tf.constant([[3., 3.]])
    matrix2 = tf.constant([[2.],[2.]])
    product = tf.matmul(matrix1, matrix2)
    # ...
```

&emsp;&emsp;设备用字符串进行标识. 目前支持的设备包括:

&emsp;&emsp;- "/cpu:0": 机器的 CPU.

&emsp;&emsp;- "/gpu:0": 机器的第一个 GPU, 如果有的话.

&emsp;&emsp;- "/gpu:1": 机器的第二个 GPU, 以此类推.


### 1.1.4 交互式使用

&emsp;&emsp;文档中的 Python 示例使用一个会话 Session 来 启动图, 并调用 Session.run() 方法执行操作.

&emsp;&emsp;为了便于使用诸如 IPython 之类的 Python 交互环境, 可以使用 InteractiveSession 代替 Session 类, 使用 Tensor.eval() 和 Operation.run() 方法代替 Session.run(). 这样可以避免使用一个变量来持有会话.

```python
# 进入一个交互式 TensorFlow 会话.
import tensorflow as tf
sess = tf.InteractiveSession()

x = tf.Variable([1.0, 2.0])
a = tf.constant([3.0, 3.0])

# 使用初始化器 initializer op 的 run() 方法初始化 'x' 
x.initializer.run()

# 增加一个减法 sub op, 从 'x' 减去 'a'. 运行减法 op, 输出结果 
sub = tf.sub(x, a)
print sub.eval()
# ==> [-2. -1.]
```

<br>

### 1.2 Tensor

#### 1.2.1 变量

&emsp;&emsp;变量维护图执行过程中的状态信息. 下面的例子演示了如何使用变量实现一个简单的计数器. 

```python
# 创建一个变量，初始化为标量0
state = tf.Variable(0, name = 'counter')

# 创建一个op，其作用是使state增加1
one = tf.constant(1)
new_value = tf.add(state, one)
update = tf.assign(state, new_value)

# 启动图后，变量必须先经过'初始化'（init）op初始化
# 首先必须增加一个'初始化'op到图中
init_op = tf.initialize_all_variables()

# 启动图，运行op
with tf.Session() as sess:
    # 运行 'init' op
    sess.run(init_op)
    # 打印 'state'的初始值
    print(sess.run(state))
    # 运行op，更新'state'，并打印'state'
    for _ in range(3):
        sess.run(update)
        print(sess.run(state))

# 输出:
# 0
# 1
# 2
# 3
```

&emsp;&emsp;代码中 assign() 操作是图所描绘的表达式的一部分, 正如 add() 操作一样. 所以在调用 run() 执行表达式之前, 它并不会真正执行赋值操作.

&emsp;&emsp;通常会将一个统计模型中的参数表示为一组变量. 例如, 你可以将一个神经网络的权重作为某个变量存储在一个 tensor 中. 在训练过程中, 通过重复运行训练图, 更新这个 tensor.

#### 1.2.2 Fetch

&emsp;&emsp;为了取回操作的输出内容, 可以在使用 Session 对象的 run() 调用 执行图时, 传入一些 tensor, 这些 tensor 会帮助你取回结果. 在之前的例子里, 我们只取回了单个节点 state, 但是你也可以取回多个 tensor:

```python
input1 = tf.constant(3.0)
input2 = tf.constant(2.0)
input3 = tf.constant(5.0)
intermed = tf.add(input2, input3)
mul = tf.mul(input1, intermed)

with tf.Session():
  result = sess.run([mul, intermed])
  print result

# 输出:
# [array([ 21.], dtype=float32), array([ 7.], dtype=float32)]
```

#### 1.2.3 Feed

&emsp;&emsp;上述示例在计算图中引入了 tensor, 以常量或变量的形式存储. TensorFlow 还提供了 feed 机制, 该机制 可以临时替代图中的任意操作中的 tensor 可以对图中任何操作提交补丁, 直接插入一个 tensor.

&emsp;&emsp;feed 使用一个 tensor 值临时替换一个操作的输出结果. 你可以提供 feed 数据作为 run() 调用的参数. feed 只在调用它的方法内有效, 方法结束, feed 就会消失. 最常见的用例是将某些特殊的操作指定为 "feed" 操作, 标记的方法是使用 tf.placeholder() 为这些操作创建占位符.

```python
input1 = tf.placeholder(tf.types.float32)
input2 = tf.placeholder(tf.types.float32)
output = tf.mul(input1, input2)

with tf.Session() as sess:
  print sess.run([output], feed_dict={input1:[7.], input2:[2.]})

# 输出:
# [array([ 14.], dtype=float32)]
```

&emsp;&emsp;如果没有正确提供 feed, placeholder() 操作将会产生错误. 



<br>
<br>
<br>
<br>

## Reference:

1.[TensoFlow官方教程-基本使用](http://www.tensorfly.cn/tfdoc/get_started/basic_usage.html)















