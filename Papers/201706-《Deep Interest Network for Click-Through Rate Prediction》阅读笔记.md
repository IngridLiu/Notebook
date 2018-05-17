##《Deep Interest Network for Click-Through Rate Prediction》阅读笔记

### 1 （Motivation）Introduction
&emsp;&emsp;在以每次点击成本（cost-per-click，CPC）衡量的广告系统中，广告根据每千米有效成本（effective cost per mille，eCPM）进行排序。每千米有效成本（effective cost per mille，eCPM）由竞价（bid price）和点击率（click-through rate，CTR）表示而成，点击率（click-through rate，CTR）由系统生成。点击率（click-through rate，CTR）的预测对于广告系统具有至关重要的意义。
&emsp;&emsp;受到深度学习在计算机视觉和自然语言领域应用广泛且成效优异的启发，很多基于深度学习的点击率预测模型被提出。这些基于Embedding&MLP的模型一般思路是将原始的高维稀疏特征映射到一个低维空间中，也即对原始特征做了embedding操作，之后将这些特征分组变换为定长向量，最后将它们合并到一起，通过一个全连接网络学习到特征间的交互信息和最终与CTR之间的非线性关系。
&emsp;&emsp;受到Embedding&MLP仅能使用有限的向量长度来表示用户特征的限制，无法表示出用户的兴趣多样性。而用户的兴趣是多种多样的，若要增强向量对用户兴趣多样性的表达能力，需要大量扩大向量维度，而这会引起模型规模增大，易发生过拟合以及计算资源不足的问题。另一方面，用户的行为仅会受到其部分兴趣的影响，例如用户是否会购买护目镜取决于用户上周购买了泳衣而并非鞋子。
&emsp;&emsp;因此，作者提出了一个新的模型，深度兴趣网络（DIN），它通过考虑用户对候选广告的历史行为数据来适应性地计算用户兴趣的表示向量。通过引入本地激活单元，DIN关注（Attention）用户的相关兴趣，这些兴趣通过软搜索用户历史行为的相关部分来获取。并使用加权池化（weighted sum pooling）来获取用户对候选广告的兴趣表示。这增强了模型在有限维度下的表达能力，并且使DIN能够更好的获取用户兴趣的多样性。
&emsp;&emsp;同时针对大规模数据的稀疏问题，作者提出了小批次数据感知正则化（mini-batch aware regularization），mini-batch中只有非零特征的参数参与L2-norm的计算，使得这样的计算规模是可以接受的。此外，作者还设计了数据适应性激活函数（a data adaptive activation function），该函数推广了PReLU，能够适应性的修正输入点的贡献值，实验证明，该激活函数对于训练稀疏特征有所帮助。
<br>







## Reference：
1. [《Deep Interest Network for Click-Through Rate Prediction》阅读笔记](https://zhuanlan.zhihu.com/p/30597671)
