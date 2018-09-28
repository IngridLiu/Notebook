# 2 hdfs集群集中管理和hadoop文件操作

<br>

| 转自[马士兵hadoop第二课：hdfs集群集中管理和hadoop文件操作](http://www.cnblogs.com/yucongblog/p/6650834.html)

<br>
<br>
<br>
<br>

## 1 HDFS架构

&emsp;&emsp;一个简单的HDFS架构由一个namenode（2.X版本最多两个namenode）和若干个datanode构成，其中namenode存储元数据，datanode存储数据。

### 1.1 Namenode

&emsp;&emsp;namenode存储文件系统元数据，包括文件目录结构、分块情况、每块位置、权限等，这些数据都存在内存中。也就意味着namenode的内存要求很大。

### 1.2 Datanode

&emsp;&emsp;datanode存储数据，在hdfs中将数据按照块进行存储，每一块的大小默认为128M。

&emsp;&emsp;当有一个文件存储到hdfs中时，namenode会将该文件分为大小为128M的一个个块，再将各个块存储到datanode上去，hadoop默认将数据备份两份，即每份数据存储三份。



<br>

## 2 处理集群

### 2.1 观察集群情况

#### 2.1.1 观察集群配置情况

```bash
[root@master ~]# hdfs dfsadmin -report
```
&emsp;&emsp;将依次查看namenode和各个datanode的配置情况。

#### 2.1.2 web界面观察集群运行情况

&emsp;&emsp;使用netstat命令查看端口监听

```bash
[root@master ~]# netstat -ntlp
```

![](https://images2015.cnblogs.com/blog/761746/201704/761746-20170401094236414-976025229.png)

&emsp;&emsp;浏览器地址栏输入：http://192.168.56.100:50070,在web界面可以查看各个node运行的情况。

![](https://images2015.cnblogs.com/blog/761746/201704/761746-20170401093928758-1861932371.png)

### 2.2 对集群进行集中管理

1. 先使用手工关闭集群。依次在各个节点terminal输入：

```bash
[root@master hadoop]# hadoop-daemon.sh stop namenode[datanode]
```

2. 修改master上的/usr/local/hadoop/etc/hadoop/slaves文件

```bash
[root@master hadoop]# vim slaves
```

&emsp;&emsp;依次输入以下内容

```bash
#编辑内容如下
slave1
slave2
slave3
```

3. 使用strat-dfs.sh启动集群

```bash
[root@master hadoop]# start-dfs.sh
```

&emsp;&emsp;此时需要远程登录到slave上，根据命令需求，依次需要输入master的密码，slave1、slave2、slave3的

&emsp;&emsp;使用start-dfs.sh命令，默认需要启动secondary namenode，需要secondary namenode的密码。

&emsp;&emsp;发现需要输入每个节点的密码，太过于繁琐，于是需要配置免密ssh远程登陆。

&emsp;&emsp;在master上用ssh连接一台slave，需要输入密码slave的密码，

```bash
[root@master hadoop]# ssh slave1
```
&emsp;&emsp;需要输入密码，输入密码登陆成功后，使用exit指令退回到master。

4.免密ssh远程登陆

&emsp;&emsp;生成rsa算法的公钥和私钥

```bash
[root@master hadoop]# ssh-keygen -t rsa [然后四个回车]
```

&emsp;&emsp;进入到/root/.ssh文件夹，可看到生成了id_rsa和id_rsa.pub两个文件。

&emsp;&emsp;使用以下指令完成免密ssh登陆

```bash
[root@master hadoop]# ssh-copy-id slaveX
```

&emsp;&emsp;使用stop-dfs.sh停止集群，然后使用start-dfs.sh启动集群。

```bash
[root@master ~]# stop-dfs.sh 
```

```bash
[root@master ~]# start-dfs.sh 
```

5. 修改windows上的hosts文件，通过名字来访问集群web界面

&emsp;&emsp;编辑C:\Windows\System32\drivers\etc\hosts

```bash
192.168.56.100 master
```

&emsp;&emsp;然后就可以使用http://master:50070代替http://192.168.56.100:50070

6. 使用hdfs dfs 或者 hadoop fs命令对文件进行增删改查的操作

```bash
hadoop fs -ls /
hadoop fs -put file /
hadoop fs -mkdir /dirname
hadoop fs -text /filename
hadoop fs -rm /filename
```

将hadoop的安装文件put到了hadoop上操作如下

```bash
[root@master local]# hadoop -fs put ./hadoop-2.7.3.tar.gz /
```

![](https://images2015.cnblogs.com/blog/761746/201704/761746-20170401103311742-1681568432.png)

通过网页观察文件情况

![](https://images2015.cnblogs.com/blog/761746/201704/761746-20170401103518961-910282417.png)

7.将dfs-site.xml的replication值设为2

replication参数是分块拷贝份数，hadoop默认为3。

也就是说，一块数据会至少在3台slave上都存在，假如slave节点超过3台了。

vim hdfs-site.xml

```xml
<?xml version="1.0" encoding="UTF-8"?>
<?xml-stylesheet type="text/xsl" href="configuration.xsl"?>
<configuration>
  <property>
    <name>dfs.replication</name>  
    <value>2</value>
  </property>
  <property>
    <name>dfs.namenode.heartbeat.recheck-interval</name>
    <value>10000</value>
  </property>
</configuration>

```

&emsp;&emsp;为了方便测试，同时需要修改另外一个参数dfs.namenode.heartbeat.recheck-interval，这个值默认为300s，

&emsp;&emsp;将其修改成10000，单位是ms，这个参数是定期间隔时间后检查slave的运行情况并更新slave的状态。

&emsp;&emsp;可以通过 hadoop-2.7.3\share\doc\hadoop\index.html里面查找这些默认的属性

![](https://images2015.cnblogs.com/blog/761746/201704/761746-20170401105644680-1459493321.png)

![](https://images2015.cnblogs.com/blog/761746/201704/761746-20170401105613070-1143864292.png)

修改完hdf-size.xml文件后，重启hadoop集群，

```bash
stop-dfs.sh  #停止hadoop集群
start-dfs.sh #启动hadoop集权
```

```bash
hadoop -fs put ./jdk-8u91-linux-x64.rpm / #将jdk安装包上传到hadoop的根目录
```

&emsp;&emsp;到web页面上去观察jdk安装包文件分块在slave1，slave2，slave3的存储情况

```bash
hadoop-daemon.sh stop datanode #在slave3上停掉datanode
```

&emsp;&emsp;等一会时间后（大概10s，前面修改了扫描slave运行情况的间隔时间为10s），刷新web页面

&emsp;&emsp;观察到slave3节点挂掉

```bash
hadoop-daemon.sh start datanode #在slave3上启动datanode
```

&emsp;&emsp;然后再去观察jdk安装包文件分块在slave1，slave2，slave3的存储情况

