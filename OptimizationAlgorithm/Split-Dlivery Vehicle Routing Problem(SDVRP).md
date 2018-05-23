# 需求可拆分车辆路径问题（Split-Dlivery Vehicle Routing Problem，SDVRP)
<br>
<br>
<br>

## 1 问题的提出
&emsp;&emsp;在图中有一个中心点A，由N个需求点Bi，每个需求点的需求为Di，由需求点Bi到Bj的成本为cij，一辆车的容量为Q，请问如何安排车辆（车辆数量已给定）使总的成本最低。
<br>

## 2 解的表示
&emsp;&emsp;在问题中需要做三个决策：如何将需求点分配给车辆、每个需求点分配给车辆的需求量为多少以及车辆访问需求点的顺序。目标值只和访问顺序有关。
### 2.1 构造树对路径进行分配
&emsp;&emsp;利用图表示分配关系，圈表示需求点，方形表示车辆。
&emsp;&emsp;可以证明如果该问题有可行解，则肯定存在一个最优解不存在环，我们总可以找到一个最优解为树（or森林）。则解的表示如下图1所示。
&emsp;&emsp;[见ppt图]()
&emsp;&emsp;在初始树中， 车的数量已给定。初始解可以任意确定，通过启发式算法求解。
### 2.2 确定每个需求点分配给车辆的需求量
&emsp;&emsp;初始解的构造，在一条路径中，首先提供全部的需求给由该路径单独供给的需求点，尽可能多的分配给需求被拆分的点。
&emsp;&emsp;从任意路径开始进行分配均可。
&emsp;&emsp;不会出现多个点被多辆车共同分配的情况，因为不会成环。如上所诉。

<br>

## 3 邻域的设计