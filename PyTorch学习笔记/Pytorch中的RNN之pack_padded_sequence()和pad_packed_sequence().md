# Pytorch中的RNN之pack_padded_sequence()和pad_packed_sequence()

<br>
<br>

## 1. 为什么有pad和pack操作？

&emsp;&emsp;在使用深度学习特别是LSTM进行文本分析时，经常会遇到文本长度不一样的情况，此时就需要对同一个batch中的不同文本使用padding的方式进行文本长度对齐，方便将训练数据输入到LSTM模型进行训练，同时为了保证模型训练的精度，应该同时告诉LSTM相关padding的情况，此时，pytorch中的pack_padded_sequence就有了用武之地。

&emsp;&emsp;先看一个例子，这个batch中有5个sample

![](https://img2018.cnblogs.com/blog/1404499/201905/1404499-20190505155222782-897343380.png)

&emsp;&emsp;如果不用pack和pad操作会有一个问题，什么问题呢？比如上图，句子“Yes”只有一个单词，但是padding了多余的pad符号，这样会导致LSTM对它的表示通过了非常多无用的字符，这样得到的句子表示就会有误差，更直观的如下图：

![](https://img2018.cnblogs.com/blog/1404499/201905/1404499-20190505155104163-1230971019.png)

&emsp;&emsp;那么我们正确的做法应该是怎么样呢？

&emsp;&emsp;在上面这个例子，我们想要得到的表示仅仅是LSTM过完单词"Yes"之后的表示，而不是通过了多个无用的“Pad”得到的表示：如下图：

![](https://img2018.cnblogs.com/blog/1404499/201905/1404499-20190505155131859-1415302798.png)

<br>

## 1. torch.nn.utils.rnn.pack_padded_sequence()

&emsp;&emsp;这里的pack，理解成压紧比较好。 将一个 填充过的变长序列 压紧。（填充时候，会有冗余，所以压紧一下）

&emsp;&emsp;其中pack的过程为：（注意pack的形式，不是按行压，而是按列压）

![（下面方框内为PackedSequence对象，由data和batch_sizes组成）](https://img2018.cnblogs.com/blog/1404499/201810/1404499-20181022223531597-1352808756.png)

&emsp;&emsp;pack之后，原来填充的 PAD（一般初始化为0）占位符被删掉了。

&emsp;&emsp;输入的形状可以是(T×B×* )。T是最长序列长度，B是batch size，*代表任意维度(可以是0)。如果batch_first=True的话，那么相应的 input size 就是 (B×T×*)。

&emsp;&emsp;Variable中保存的序列，应该按序列长度的长短排序，长的在前，短的在后。即input[:,0]代表的是最长的序列，input[:, B-1]保存的是最短的序列。

&emsp;&emsp;NOTE： 只要是维度大于等于2的input都可以作为这个函数的参数。你可以用它来打包labels，然后用RNN的输出和打包后的labels来计算loss。通过PackedSequence对象的.data属性可以获取 Variable。

&emsp;&emsp;参数说明:

&emsp;&emsp;- input (Variable) – 变长序列 被填充后的 batch

&emsp;&emsp;- lengths (list[int]) – Variable 中 每个序列的长度。

&emsp;&emsp;- batch_first (bool, optional) – 如果是True，input的形状应该是B*T*size。

&emsp;&emsp;返回值:

&emsp;&emsp;一个PackedSequence 对象。

<br>

## 3. torch.nn.utils.rnn.pad_packed_sequence()

&emsp;&emsp;填充packed_sequence。

&emsp;&emsp;上面提到的函数的功能是将一个填充后的变长序列压紧。 这个操作和pack_padded_sequence()是相反的。把压紧的序列再填充回来。填充时会初始化为0。

&emsp;&emsp;返回的Varaible的值的size是 T×B×*, T 是最长序列的长度，B 是 batch_size,如果 batch_first=True,那么返回值是B×T×*。

&emsp;&emsp;Batch中的元素将会以它们长度的逆序排列。

&emsp;&emsp;参数说明:

&emsp;&emsp;- sequence (PackedSequence) – 将要被填充的 batch

&emsp;&emsp;- batch_first (bool, optional) – 如果为True，返回的数据的格式为 B×T×*。

&emsp;&emsp;返回值: 一个tuple，包含被填充后的序列，和batch中序列的长度列表




## Reference:

1. [pytorch里的pack_padded_sequence和pad_packed_sequence解析](https://blog.csdn.net/lssc4205/article/details/79474735)

2. [Pytorch中的RNN之pack_padded_sequence()和pad_packed_sequence()](https://www.cnblogs.com/sbj123456789/p/9834018.html)