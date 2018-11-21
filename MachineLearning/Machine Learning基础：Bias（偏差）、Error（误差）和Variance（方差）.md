# Machine Learning基础：Bias（偏差）、Error（误差）和Variance（方差）

<br>
<br>



&emsp;&emsp;首先明确一点，Bias和Variance是针对Generalization（一般化，泛化）来说的。

&emsp;&emsp;在机器学习中，我们用训练数据集去训练（学习）一个model（模型），通常的做法是定义一个Loss function（误差函数），通过将这个Loss（或者叫error）的最小化过程，来提高模型的性能（performance）。然而我们学习一个模型的目的是为了解决实际的问题（或者说是训练数据集这个领域（field）中的一般化问题），单纯地将训练数据集的loss最小化，并不能保证在解决更一般的问题时模型仍然是最优，甚至不能保证模型是可用的。这个训练数据集的loss与一般化的数据集的loss之间的差异就叫做generalization error。

&emsp;&emsp;而generalization error又可以细分为Bias和Variance两个部分。

&emsp;&emsp;首先如果我们能够获得所有可能的数据集合，并在这个数据集合上将loss最小化，这样学习到的模型就可以称之为“真实模型”，当然，我们是无论如何都不能获得并训练所有可能的数据的，所以“真实模型”肯定存在，但无法获得，我们的最终目标就是去学习一个模型使其更加接近这个真实模型。

&emsp;&emsp;而bias和variance分别从两个方面来描述了我们学习到的模型与真实模型之间的差距。

&emsp;&emsp;Bias是 “用所有可能的训练数据集训练出的所有模型的输出的平均值” 与 “真实模型”的输出值之间的差异；

&emsp;&emsp;Variance则是“不同的训练数据集训练出的模型”的输出值之间的差异。

&emsp;&emsp;这里需要注意的是我们能够用来学习的训练数据集只是全部数据中的一个子集。想象一下我们现在收集几组不同的数据，因为每一组数据的不同，我们学习到模型的最小loss值也会有所不同，当然，它们与“真实模型”的最小loss也是不一样的。

&emsp;&emsp;看下图可以理解的更直观：

![](https://upload-images.jianshu.io/upload_images/10947003-46293216c972fb41.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/600)

<br>
<br>
<br>
<br>

## Reference:

1. [机器学习中的Bias(偏差)，Error(误差)，和Variance(方差)有什么区别和联系？](https://www.zhihu.com/question/27068705)

