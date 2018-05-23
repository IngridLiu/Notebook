# 贪心随机自适应搜索算法(Greedy Randomized Adaptive Search Procedure,GRASP）
<br>
<br>
<br>

## 1. GRASP算法的基本思想
&emsp;&emsp;GRASP算法是一个多起点的迭代过程，每一次迭代由两个阶段组成：一是产生可行解的构造阶段；二是寻找局部最优解的局搜索阶段。如果局部最优解S比当前搜索到的最优解S*还要优的话，就更新S*。
&emsp;&emsp;该算法的基本架构如下：
[](https://upload-images.jianshu.io/upload_images/10947003-a31543dac2fc10eb.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/800)
&emsp;&emsp;在该算法中，Max_Iterations是迭代次数，迭代之前先贪心随机构造一个解，然后判断可行不可行，若不可行则进入Repair函数进行修正，对可行解进行局部搜索，然后更新最优解。
### 2. 可行解的构造


