# 《Deep Interest Network for Click-Through Rate Prediction》阅读笔记

## 1 Introduction
&emsp;&emsp;在以每次点击成本（cost-per-click，CPC）衡量的广告系统中，广告根据每千米有效成本（effective cost per mille，eCPM）进行排序。每千米有效成本（effective cost per mille，eCPM）由竞价（bid price）和点击率（click-through rate，CTR）表示而成，点击率（click-through rate，CTR）由系统生成。点击率（click-through rate，CTR）的预测对于广告系统具有至关重要的意义。
&emsp;&emsp;受到深度学习在计算机视觉和自然语言领域应用广泛且成效优异的启发，很多基于深度学习的点击率预测模型被提出。这些模型一般思路是将原始的高维稀疏特征映射到一个低维空间中，也即对原始特征做了embedding操作，之后将这些特征分组变换为定长向量，最后将它们合并到一起，通过一个全连接网络学习到特征间的交互信息和最终与CTR之间的非线性关系。