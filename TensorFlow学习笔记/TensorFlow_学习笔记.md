# TensorFlow学习笔记.md

<br>
<br>


## 1. TensorFlow基本使用

在TensorFlow中：

- 使用图（graph）来表示计算任务；

- 在被称之为会话（Session）的上下文（context）中执行图；

- 使用tensor表示数据；

- 通过变量（Variable）维护状态；

- 使用feed和fetch可以为任意的操作（arbitrary operation）赋值或者从其中获取数据；

TensorFlow 是一个编程系统, 使用图来表示计算任务. 图中的节点被称之为 op (operation 的缩写). 一个 op 获得 0 个或多个 Tensor, 执行计算, 产生 0 个或多个 Tensor. 每个 Tensor 是一个类型化的多维数组. 例如, 你可以将一小组图像集表示为一个四维浮点数数组, 这四个维度分别是 [batch, height, width, channels].

一个 TensorFlow 图描述了计算的过程. 为了进行计算, 图必须在 会话 里被启动. 会话 将图的 op 分发到诸如 CPU 或 GPU 之类的 设备 上, 同时提供执行 op 的方法. 这些方法执行后, 将产生的 tensor 返回. 在 Python 语言中, 返回的 tensor 是 numpy ndarray 对象; 

### 1.1 图

#### 1.1.1 计算图

TensorFlow 程序通常被组织成一个构建阶段和一个执行阶段. 在构建阶段, op 的执行步骤 被描述成一个图. 在执行阶段, 使用会话执行执行图中的 op.

例如, 通常在构建阶段创建一个图来表示和训练神经网络, 然后在执行阶段反复执行图中的训练 op.

#### 1.1.2 构建图

构建图的第一步, 是创建源 op (source op). 源 op 不需要任何输入, 例如 常量 (Constant). 源 op 的输出被传递给其它 op 做运算.

Python 库中, op 构造器的返回值代表被构造出的 op 的输出, 这些返回值可以传递给其它 op 构造器作为输入.

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

默认图现在有三个节点，两个constant() op,和一个matmul() op。为了真正进行矩阵相乘运算, 并得到矩阵乘法的 结果, 你必须在会话里启动这个图.

#### 1.1.3 在一个会话中启动图

构造阶段完成后, 才能启动图. 启动图的第一步是创建一个 Session 对象, 如果无任何创建参数, 会话构造器将启动默认图.

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

Session 对象在使用完后需要关闭以释放资源. 除了显式调用 close 外, 也可以使用 "with" 代码块 来自动完成关闭动作.

```python
with tf.Session() as sess:
  result = sess.run([product])
  print result
```

在实现上, TensorFlow 将图形定义转换成分布式执行的操作, 以充分利用可用的计算资源(如 CPU 或 GPU). 一般你不需要显式指定使用 CPU 还是 GPU, TensorFlow 能自动检测. 如果检测到 GPU, TensorFlow 会尽可能地利用找到的第一个 GPU 来执行操作.

如果机器上有超过一个可用的 GPU, 除第一个外的其它 GPU 默认是不参与计算的. 为了让 TensorFlow 使用这些 GPU, 你必须将 op 明确指派给它们执行. with...Device 语句用来指派特定的 CPU 或 GPU 执行操作:

```python
with tf.Session() as sess:
  with tf.device("/gpu:1"):
    matrix1 = tf.constant([[3., 3.]])
    matrix2 = tf.constant([[2.],[2.]])
    product = tf.matmul(matrix1, matrix2)
    # ...
```

设备用字符串进行标识. 目前支持的设备包括:

- "/cpu:0": 机器的 CPU.
- "/gpu:0": 机器的第一个 GPU, 如果有的话.
- "/gpu:1": 机器的第二个 GPU, 以此类推.

























