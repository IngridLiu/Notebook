# 散射搜索法（Scatter Search， SS）
&emsp;&emsp;散射搜索法(Scatter search, SS)作为一种新兴的演化算法已成功应用到很多领域，如分配、图论、商业软件以及线性排序等问题，目前已成为组合优化问题求解的一个有效方法。

## 1

## 2 求解流程：
![图1：SS算法流程](https://upload-images.jianshu.io/upload_images/10947003-3600a555b890c598.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
&emsp;&emsp;SS算法流程如图1所示，主要由五个部分组成。
（1）多样解生成
&emsp;&emsp;由于SS的基本机制是参考集组合生成新解，因此参考集中一般不允许存在两个相同的解，这样在初始化时必须保持种群的多样性。对实数编码的优化问题，常用受控的随机方法和频率记忆方法。
（2）新解改进
&emsp;&emsp;改进方法一般是用在对散射搜索法的多样性初始解和组合方法产生的新解进行改进。如可以采用梯度下降法和Nelder-Mead直接搜索法（复合型法）等多种方法。
（3）参考解集更新
&emsp;&emsp;参考集是散射搜索法的核心。若参考集缺乏多样性，即使通过组合和改进的方法，也不会产生更好解，因为多样性为子集生成方法提供了基本结构。因此，现有SS应用中一般把参考集（RefSet）分为两部分：优质解参考集（RefSet1）和多样性解参考集（RefSet2）。设参考集RefSet的数目为b=b1+b2，其中b1和b2分别为RefSet1和RefSet2中参考解的数量。参考集的更新方法一般有动态和静态两种。
（4）子集生成
&emsp;&emsp;子集是SS组合的基础。一般的子集生成方法是包含2个解的子集生成法，即对参考集中b个解进行两两组合，构成解对(Pairs)，则共有b(b-1)/2个子集。以此基础，则可以衍生出其它子集生成方法。目前实验表明，SS的搜索能力相当程度上取决于解对的组合。
（5）参考解的组合法
&emsp;&emsp;组合方法一般取决于所要解决问题的特点。不少优化问题可以采取线性组合法。
&emsp;&emsp;Scatter search的基本过程是，首先利用多样性解生成法生成多样性初始解，并用新解改进法对每一个解进行改进，加入初始种群P；根据解质量(目标函数值优劣)和多样性指标，从P选择若干个解构成初始参考集(RefSet)。然后利用子集生成法从RefSet中系统化生成一系列子集，对这些子集中的解利用组合法策略化地生成新的解，然后利用新解改进法对该新解进行改进，进而利用该解对参考集进行更新，反复执行上述过程，直到满足结束准则。
&emsp;&emsp;SS算法伪代码如图2所示：
![图2：SS算法伪代码](https://upload-images.jianshu.io/upload_images/10947003-ba3763c77c9d702d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

## 3 算例
![图3：TSP问题](https://upload-images.jianshu.io/upload_images/10947003-e0123827de9895b5.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
&emsp;&emsp;如图3所示，是一个TSP问题的示例。
&emsp;&emsp;一个TSP问题的示例。有一个供应点，若n（n=14）个需求点，每个需求点的需求为<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;q=(q_i)=(0,&space;6,&space;20,&space;8,&space;9,&space;10,&space;8,&space;7,&space;5,&space;5,&space;4,&space;3,&space;4,&space;7)" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;q=(q_i)=(0,&space;6,&space;20,&space;8,&space;9,&space;10,&space;8,&space;7,&space;5,&space;5,&space;4,&space;3,&space;4,&space;7)" title="q=(q_i)=(0, 6, 20, 8, 9, 10, 8, 7, 5, 5, 4, 3, 4, 7)" /></a>，以及m(<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;m&space;\in&space;[1,14]" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;m&space;\in&space;[1,14]" title="m \in [1,14]" /></a>)辆车将货物从供应点运送到需求点，其中每辆车的容量为30。每两点之间的距离如下图4所示，其中点0为供应点。请问如何安排运输，使总的运输路径最短。
![图4：点之间的距离](https://upload-images.jianshu.io/upload_images/10947003-339906f2fe60e8c8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
1. 产生满足多样化条件的解
&emsp;&emsp;首先，定义一个种子解为P={1，2，3，4，5，6，7，8，9，10，11，12，13，14}。只需要产生满足多样性的解，并不需要产生最优的解。
&emsp;&emsp;定义P(h, s)=(s, s + h, s + 2h, …, s + rh) , 其中 1 ≤ s ≤ h and s + rh ≤ n.
&emsp;&emsp;例如，P(4: s) for s=4, …, 1 是: P(4: 4)={4, 8, 12}, P(4:3)={3, 7, 11}, P(4:2)={2, 6, 10, 14}及P(4:1)={1, 5, 9, 13}。
&emsp;&emsp;因此：P(4) = {4, 8, 12, 3, 7, 11, 2, 6, 10, 14, 1, 5, 9, 13}. 
2. 对满足多样化条件的解生成路径
![图5:生成路径](https://upload-images.jianshu.io/upload_images/10947003-626020f0de97777c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
&emsp;&emsp;对于第1步中生成的满足多样化条件的解，从第一个点开始依次加入路径，遇到无法满足容量30的点，则生成新的路径。则如图5所示，可以生成五条路径。
3. 利用2-Opt算子改进路径
![图6:2-Opt改进过程](https://upload-images.jianshu.io/upload_images/10947003-ce6d1844ff1f511e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
&emsp;&emsp;如图6所示，任意更改路径中两个需求点的访问顺序，求得总路径。
&emsp;&emsp;则对于每一个满足多样化条件的点<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;T_k" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;T_k" title="T_k" /></a>，可以得到如下图7所示的结果<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;S_k" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;S_k" title="S_k" /></a>。
![图7:每个满足多样化的结果改进之后的结果](https://upload-images.jianshu.io/upload_images/10947003-1126cf843c3aa1af.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
4. 改进解方法
&emsp;&emsp;对于每一个解，选择一条路径中的点，加入其他路径当中，使Cost。则对于以上得出的10个解，改进得到新的<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;S_k" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;S_k" title="S_k" /></a>如下图8所示。
![图8:改进解得到的结果](https://upload-images.jianshu.io/upload_images/10947003-3eccb572fac66cd5.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
5. 参考集更新方法
&emsp;&emsp;更新参考集需要在紧密型和多样性之间（intensification and diversification）取得平衡。紧密型表示取得的解的质量（解的结果更好），多样化表示与当前解的差异。则参考集RS可以由两个子集B（high-quality）和D（diverse）构成。
&emsp;&emsp;考虑一个候选集CS={S1, …, S10}和一个大小为 |RS| = 6的参考集, 其中|B|=|D| = 3。我们应当消除CS中解的重复。选择CS中最好的解 S7, S2 和 S4 产生子集B.我们产生与当前RS中差异最大的解来产生D。作为一种产生差异的措施，我们用<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;d_ij&space;=&space;|(S_i\cup&space;S_j&space;)\(S_i\cap&space;S_j)|" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;d_ij&space;=&space;|(S_i\cup&space;S_j&space;)\(S_i\cap&space;S_j)|" title="d_ij = |(S_i\cup S_j )\(S_i\cap S_j)|" /></a>表示<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;S_i" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;S_i" title="S_i" /></a>和<a href="http://www.codecogs.com/eqnedit.php?latex=\inline&space;S_j" target="_blank"><img src="http://latex.codecogs.com/gif.latex?\inline&space;S_j" title="S_j" /></a>解之间的差异性。
&emsp;&emsp;例如，S3包含六条边(1,8), (3,7), (4,10), (9,0), (9,12), (11,13),这些边不在S4中, S4有7条边(1,7), (3,0), (4,8), (9,10), (9,11), (12,0), (13,0),这些变不在 S3中. 因此这两条边之间的差异是13.
&emsp;&emsp;B中选择最小差异的三个最大值作为参考集中的B，差异最大的三个值作为参考集中的D。
&emsp;&emsp;
&emsp;&emsp;
&emsp;&emsp;
&emsp;&emsp;
&emsp;&emsp;
&emsp;&emsp;
&emsp;&emsp;

