# 自主学习（Self-Paced Learning）
 
<br>
<br>

## 1. 自主学习(Self-Paced Learing)

&emsp;&emsp;自主学习（Self-Paced Learning）类似于主动学习（active learning）从未知标签中选取数据加入已知标签训练，不同的是，主动学习每次选取具有特征最丰富的点，然后将这个点返回到数据库中去查询，得到一个LABEL然后去更新分类器。然而，自主学习起源于课程学习（curriculum learning），它根据学生的学习能力去选取课程，因而自主学习每次选取最简单的特征点集，然后到复杂，每次选取的个数不同，这样训练的好处就是减少熵值，训练出潜在的权重参数。

&emsp;&emsp;自主学习的目标：

![](https://img-blog.csdn.net/20180603103302232?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3l4ejMwMjQ=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

&emsp;&emsp;其潜在权重为V.选取的方式有很多种，每篇论文都会提出一个方法。

&emsp;&emsp;但是，在我近期看的论文中，用 negative l1-norm regularizer方法：

![](https://img-blog.csdn.net/20180603103657321?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3l4ejMwMjQ=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

&emsp;&emsp;同时作者还提出了一个多样性的方法the negative l2,1-norm：

![](https://img-blog.csdn.net/20180603104859185?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3l4ejMwMjQ=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)



<br>
<br>
<br>
<br>

## Reference:

1.[学习笔记：Self-Paced Learning](https://blog.csdn.net/yxz3024/article/details/80554596)


