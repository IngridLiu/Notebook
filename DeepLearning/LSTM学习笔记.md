# LSTM 学习笔记

&emsp;&emsp;本文转自：[译] 理解 LSTM 网络

<br>

## 1 RNN（Recurrent Neural Networks）

### 1.1 RNN基本内容：

&emsp;&emsp;RNN是包含循环的网络，它能够通过先前的事件推测后续的事件，允许信息的持久化。

![RNN基本结构](https://upload-images.jianshu.io/upload_images/10947003-3d50bb2d95bb347c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/150)

&emsp;&emsp;上图A是一个RNN模块的示例，输入为x_t，输出为h_t。通过模块A的循环，使得信息可以从当前传递到下一步。

&emsp;&emsp;为了便于观察和理解，通常会将RNN进行扩展，表示成计算图，如下图。

![RNN计算图](https://upload-images.jianshu.io/upload_images/10947003-fbc6de1ea3e2e110.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)

&emsp;&emsp;可以参考 Andrej Karpathy 的博客文章——The Unreasonable Effectiveness of Recurrent Neural Networks 来看看更丰富有趣的 RNN 的成功应用。


### 1.2 RNN中的长期依赖（Long-Term Dependencies）问题：

&emsp;&emsp;RNN 的关键点之一就是他们可以用来连接先前的信息到当前的任务上，例如使用过去的视频段来推测对当前段的理解。如果 RNN 可以做到这个，他们就变得非常有用。但还有很多依赖因素。

&emsp;&emsp;有时候，我们仅仅需要知道先前的信息来执行当前的任务。例如，我们有一个语言模型用来基于先前的词来预测下一个词。如果我们试着预测 “the clouds are in the sky” 最后的词，我们并不需要任何其他的上下文 —— 因此下一个词很显然就应该是 sky。在这样的场景中，相关的信息和预测的词位置之间的间隔是非常小的，RNN 可以学会使用先前的信息。此情景如下图。

![](https://upload-images.jianshu.io/upload_images/10947003-2cd7a436cff38312.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)

&emsp;&emsp;但是同样会有一些更加复杂的场景。假设我们试着去预测“I grew up in France... I speak fluent French”最后的词。当前的信息建议下一个词可能是一种语言的名字，但是如果我们需要弄清楚是什么语言，我们是需要先前提到的离当前位置很远的 France 的上下文的。这说明相关信息和当前预测位置之间的间隔就肯定变得相当的大。不幸的是，在这个间隔不断增大时，RNN 会丧失学习到连接如此远的信息的能力。此情况如下图。

![相当长的相关信息和位置间隔](https://upload-images.jianshu.io/upload_images/42741-becb05d96b1e4af7.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)

&emsp;&emsp;在理论上，RNN 绝对可以处理这样的长期依赖问题。人们可以仔细挑选参数来解决这类问题中的最初级形式，但在实践中，RNN 肯定不能够成功学习到这些知识。Bengio, et al. (1994)等人对该问题进行了深入的研究，他们发现一些使训练 RNN 变得非常困难的相当根本的原因。然而，幸运的是，LSTM 并没有这个问题！


<br>

## 2 LSTM 网络

&emsp;&emsp;Long Short Term 网络—— 一般就叫做 LSTM ——是一种 RNN 特殊的类型，可以学习长期依赖信息。LSTM 由Hochreiter & Schmidhuber (1997)提出，并在近期被Alex Graves进行了改良和推广。在很多问题，LSTM 都取得相当巨大的成功，并得到了广泛的使用。LSTM 通过刻意的设计来避免长期依赖问题。记住长期的信息在实践中是 LSTM 的默认行为，而非需要付出很大代价才能获得的能力！

&emsp;&emsp;所有 RNN 都具有一种重复神经网络模块的链式的形式。在标准的 RNN 中，这个重复的模块只有一个非常简单的结构，例如一个 tanh 层。标准RNN中的重复模块如下图。

![标准 RNN 中的重复模块包含单一的层](https://upload-images.jianshu.io/upload_images/42741-9ac355076444b66f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)

&emsp;&emsp;LSTM 同样是这样的结构，但是重复的模块拥有一个不同的结构。不同于单一神经网络层，这里是有四个，以一种非常特殊的方式进行交互。

![LSTM 中的重复模块包含四个交互的层](https://upload-images.jianshu.io/upload_images/42741-b9a16a53d58ca2b9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)

&emsp;&emsp;不必担心这里的细节。我们会一步一步地剖析 LSTM 解析图。现在，我们先来熟悉一下图中使用的各种元素的图标。

![LSTM 中的图标](https://upload-images.jianshu.io/upload_images/42741-ea943b818b8e18d0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)


&emsp;&emsp;在上面的图例中，每一条黑线传输着一整个向量，从一个节点的输出到其他节点的输入。粉色的圈代表 pointwise 的操作，诸如向量的和，而黄色的矩阵就是学习到的神经网络层。合在一起的线表示向量的连接，分开的线表示内容被复制，然后分发到不同的位置。


### 2.1 LSTM 的核心思想

&emsp;&emsp;LSTM 的关键就是细胞状态，水平线在图上方贯穿运行。细胞状态类似于传送带。直接在整个链上运行，只有一些少量的线性交互。信息在上面流传保持不变会很容易。


![细胞状态](https://upload-images.jianshu.io/upload_images/42741-ac1eb618f37a9dea.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)
        
&emsp;&emsp;LSTM 有通过精心设计的称作为“门”的结构来去除或者增加信息到细胞状态的能力。门是一种让信息选择式通过的方法。他们包含一个 sigmoid 神经网络层和一个 pointwise 乘法操作。


![“门”结构](https://upload-images.jianshu.io/upload_images/42741-7169541c790efd13.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/198)

&emsp;&emsp;Sigmoid 层输出 0 到 1 之间的数值，描述每个部分有多少量可以通过。0 代表“不许任何量通过”，1 就指“允许任意量通过”！

&emsp;&emsp;LSTM 拥有三个门，来保护和控制细胞状态。

<br>

## 3 逐步理解 LSTM

### 3.1 确定丢弃信息

&emsp;&emsp;在我们 LSTM 中的第一步是决定我们会从细胞状态中丢弃什么信息。这个决定通过一个称为忘记门层完成。该门会读取h_{t-1}和x_t，输出一个在 0 到 1 之间的数值给每个在细胞状态C_{t-1}中的数字。1 表示“完全保留”，0 表示“完全舍弃”。

&emsp;&emsp;让我们回到语言模型的例子中来基于已经看到的预测下一个词。在这个问题中，细胞状态可能包含当前主语的性别，因此正确的代词可以被选择出来。当我们看到新的主语，我们希望忘记旧的主语。

![决定丢弃信息](https://upload-images.jianshu.io/upload_images/42741-96b387f711d1d12c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)

### 3.2 确定更新信息

&emsp;&emsp;下一步是确定什么样的新信息被存放在细胞状态中。这里包含两个部分。第一，sigmoid 层称 “输入门层” 决定什么值我们将要更新。然后，一个 tanh 层创建一个新的候选值向量，\tilde{C}_t，会被加入到状态中。下一步，我们会讲这两个信息来产生对状态的更新。

&emsp;&emsp;在我们语言模型的例子中，我们希望增加新的主语的性别到细胞状态中，来替代旧的需要忘记的主语。

![确定更新信息](https://upload-images.jianshu.io/upload_images/42741-7fa07e640593f930.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)

### 3.3 更新细胞状态

&emsp;&emsp;现在是更新旧细胞状态的时间了，C_{t-1}更新为C_t。前面的步骤已经决定了将会做什么，我们现在就是实际去完成。

&emsp;&emsp;我们把旧状态与f_t相乘，丢弃掉我们确定需要丢弃的信息。接着加上i_t * \tilde{C}_t。这就是新的候选值，根据我们决定更新每个状态的程度进行变化。

&emsp;&emsp;在语言模型的例子中，这就是我们实际根据前面确定的目标，丢弃旧代词的性别信息并添加新的信息的地方。


![更新细胞状态](https://upload-images.jianshu.io/upload_images/42741-d88caa3c4faf5353.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)

### 3.4 输出信息

&emsp;&emsp;最终，我们需要确定输出什么值。这个输出将会基于我们的细胞状态，但是也是一个过滤后的版本。首先，我们运行一个 sigmoid 层来确定细胞状态的哪个部分将输出出去。接着，我们把细胞状态通过 tanh 进行处理（得到一个在 -1 到 1 之间的值）并将它和 sigmoid 门的输出相乘，最终我们仅仅会输出我们确定输出的那部分。

&emsp;&emsp;在语言模型的例子中，因为他就看到了一个代词，可能需要输出与一个动词相关的信息。例如，可能输出是否代词是单数还是负数，这样如果是动词的话，我们也知道动词需要进行的词形变化。

![输出信息](https://upload-images.jianshu.io/upload_images/42741-4c9186bf786063d6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)


<br>

## 4 LSTM 的变体

### 4.1 peephole connection

&emsp;&emsp;我们到目前为止都还在介绍正常的 LSTM。但是不是所有的 LSTM 都长成一个样子的。实际上，几乎所有包含 LSTM 的论文都采用了微小的变体。差异非常小，但是也值得拿出来讲一下。

&emsp;&emsp;其中一个流形的 LSTM 变体，就是由Gers & Schmidhuber (2000)提出的，增加了 “peephole connection”。是说，我们让 门层 也会接受细胞状态的输入。

![peephole 连接](https://upload-images.jianshu.io/upload_images/42741-0f80ad5540ea27f9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)

&emsp;&emsp;上面的图例中，我们增加了 peephole 到每个门上，但是许多论文会加入部分的 peephole 而非所有都加。

### 4.2 coupled 忘记门和输入门

&emsp;&emsp;另一个变体是通过使用 coupled 忘记和输入门。不同于之前是分开确定什么忘记和需要添加什么新的信息，这里是一同做出决定。我们仅仅会当我们将要输入在当前位置时忘记。我们仅仅输入新的值到那些我们已经忘记旧的信息的那些状态 。


![coupled 忘记门和输入门](https://upload-images.jianshu.io/upload_images/42741-bd2f1feaea22630e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)


### 4.3 GRU

&emsp;&emsp;另一个改动较大的变体是 Gated Recurrent Unit (GRU)，这是由Cho, et al. (2014)提出。它将忘记门和输入门合成了一个单一的 更新门。同样还混合了细胞状态和隐藏状态，和其他一些改动。最终的模型比标准的 LSTM 模型要简单，也是非常流行的变体。


![GRU](https://upload-images.jianshu.io/upload_images/42741-dd3d241fa44a71c0.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700)

<br>

&emsp;&emsp;这里只是部分流行的 LSTM 变体。当然还有很多其他的，如Yao, et al. (2015)提出的 Depth Gated RNN。还有用一些完全不同的观点来解决长期依赖的问题，如Koutnik, et al. (2014)提出的 Clockwork RNN。

&emsp;&emsp;要问哪个变体是最好的？其中的差异性真的重要吗？Greff, et al. (2015)给出了流行变体的比较，结论是他们基本上是一样的。Jozefowicz, et al. (2015)则在超过 1 万种 RNN 架构上进行了测试，发现一些架构在某些任务上也取得了比 LSTM 更好的结果。


![Jozefowicz等人论文截图](https://upload-images.jianshu.io/upload_images/42741-acd4c079d94803d8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/330)


<br>

## 5 结论

&emsp;&emsp;刚开始，我提到通过 RNN 得到重要的结果。本质上所有这些都可以使用 LSTM 完成。对于大多数任务确实展示了更好的性能！

&emsp;&emsp;由于 LSTM 一般是通过一系列的方程表示的，使得 LSTM 有一点令人费解。然而本文中一步一步地解释让这种困惑消除了不少。

&emsp;&emsp;LSTM 是我们在 RNN 中获得的重要成功。很自然地，我们也会考虑：哪里会有更加重大的突破呢？在研究人员间普遍的观点是：“Yes! 下一步已经有了——那就是注意力！” 这个想法是让 RNN 的每一步都从更加大的信息集中挑选信息。例如，如果你使用 RNN 来产生一个图片的描述，可能会选择图片的一个部分，根据这部分信息来产生输出的词。实际上，Xu,et al.(2015)已经这么做了——如果你希望深入探索注意力可能这就是一个有趣的起点！还有一些使用注意力的相当振奋人心的研究成果，看起来有更多的东西亟待探索……

&emsp;&emsp;注意力也不是 RNN 研究领域中唯一的发展方向。例如，Kalchbrenner,et al.(2015)提出的 Grid LSTM 看起来也是很有前途。使用生成模型的 RNN，诸如Gregor,et al.(2015)Chung,et al.(2015)和Bayer & Osendorfer (2015)提出的模型同样很有趣。在过去几年中，RNN 的研究已经相当的燃，而研究成果当然也会更加丰富！



参考：

循环神经网络（RNN）：karpathy.github.io/2015

长短期记忆单元（LSTM）：Understanding LSTM Networks（翻译版）



## Reference：
1. [LSTM（Long-Short Term Memory，长短期记忆网络）学习笔记](https://www.jianshu.com/p/ebdf394b4a4b)
2. [深度学习-模型系列】长短期记忆 LSTM](https://blog.eson.org/pub/a6941437/)