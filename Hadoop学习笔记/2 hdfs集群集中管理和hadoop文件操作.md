# hdfs集群集中管理和hadoop文件操作

<br>
<br>
<br>
<br>

## 1 HDFS架构

&emsp;&emsp;一个简单的HDFS架构由一个namenode和若干个datanode构成，其中namenode存储元数据，datanode存储数据。

### 1.1 namenode

&emsp;&emsp;namenode存储文件系统元数据，包括文件目录结构、分块情况、每块位置、权限等，这些数据都存在内存中。也就意味着namenode的内存要求很大。

### 1.2 datanode





2 观察集群配置情况

```bash
hdfs dfsadmin -report
```