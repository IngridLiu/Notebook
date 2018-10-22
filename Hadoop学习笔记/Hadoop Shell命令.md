# Hadoop Shell命令

<br>
<br>
<br>
<br>

###FS Shell 

&emsp;&emsp;调用文件系统(FS)Shell命令应使用 bin/hadoop fs <args>的形式。 所有的的FS shell命令使用URI路径作为参数。URI格式是scheme://authority/path。对HDFS文件系统，scheme是hdfs，对本地文件系统，scheme是file。其中scheme和authority参数都是可选的，如果未加指定，就会使用配置中指定的默认scheme。一个HDFS文件或目录比如/parent/child可以表示成hdfs://namenode:namenodeport/parent/child，或者更简单的/parent/child（假设你配置文件中的默认值是namenode:namenodeport）。大多数FS Shell命令的行为和对应的Unix Shell命令类似，不同之处会在下面介绍各命令使用详情时指出。出错信息会输出到stderr，其他信息输出到stdout。

**cat**

&emsp;&emsp;使用方法：hadoop fs -cat URI [URI …]

&emsp;&emsp;将路径指定文件的内容输出到stdout。

&emsp;&emsp;示例：

```bash
hadoop fs -cat hdfs://host1:port1/file1 hdfs://host2:port2/file2
hadoop fs -cat file:///file3 /user/hadoop/file4
```

&emsp;&emsp;返回值：

&emsp;&emsp;成功返回0，失败返回-1。

**chgrp**

&emsp;&emsp;使用方法：hadoop fs -chgrp [-R] GROUP URI [URI …] Change group association of files. With -R, make the change recursively through the directory structure. The user must be the owner of files, or else a super-user. Additional information is in the Permissions User Guide. -->

&emsp;&emsp;改变文件所属的组。使用-R将使改变在目录结构下递归进行。命令的使用者必须是文件的所有者或者超级用户。更多的信息请参见HDFS权限用户指南。

**chmod**

&emsp;&emsp;使用方法：hadoop fs -chmod [-R] <MODE[,MODE]... | OCTALMODE> URI [URI …]

&emsp;&emsp;改变文件的权限。使用-R将使改变在目录结构下递归进行。命令的使用者必须是文件的所有者或者超级用户。更多的信息请参见HDFS权限用户指南。

**chown**

&emsp;&emsp;使用方法：hadoop fs -chown [-R] [OWNER][:[GROUP]] URI [URI ]

&emsp;&emsp;改变文件的拥有者。使用-R将使改变在目录结构下递归进行。命令的使用者必须是超级用户。更多的信息请参见HDFS权限用户指南。

**copyFromLocal**

&emsp;&emsp;使用方法：hadoop fs -copyFromLocal <localsrc> URI

&emsp;&emsp;除了限定源路径是一个本地文件外，和put命令相似。

**copyToLocal**

&emsp;&emsp;使用方法：hadoop fs -copyToLocal [-ignorecrc] [-crc] URI <localdst>

&emsp;&emsp;除了限定目标路径是一个本地文件外，和get命令类似。

**cp**

&emsp;&emsp;使用方法：hadoop fs -cp URI [URI …] <dest>

&emsp;&emsp;将文件从源路径复制到目标路径。这个命令允许有多个源路径，此时目标路径必须是一个目录。 

&emsp;&emsp;示例：

```bash
hadoop fs -cp /user/hadoop/file1 /user/hadoop/file2
hadoop fs -cp /user/hadoop/file1 /user/hadoop/file2 /user/hadoop/dir
```

&emsp;&emsp;返回值：

&emsp;&emsp;成功返回0，失败返回-1。

**du**

&emsp;&emsp;使用方法：hadoop fs -du URI [URI …]

&emsp;&emsp;显示目录中所有文件的大小，或者当只指定一个文件时，显示此文件的大小。

&emsp;&emsp;示例：

```bash
hadoop fs -du /user/hadoop/dir1 /user/hadoop/file1 hdfs://host:port/user/hadoop/dir1 
```

&emsp;&emsp;返回值：

&emsp;&emsp;成功返回0，失败返回-1。 

**dus**

&emsp;&emsp;使用方法：hadoop fs -dus <args>

&emsp;&emsp;显示文件的大小。

**expunge**

&emsp;&emsp;使用方法：hadoop fs -expunge

&emsp;&emsp;清空回收站。请参考HDFS设计文档以获取更多关于回收站特性的信息。

**get**

&emsp;&emsp;使用方法：hadoop fs -get [-ignorecrc] [-crc] <src> <localdst> 

&emsp;&emsp;复制文件到本地文件系统。可用-ignorecrc选项复制CRC校验失败的文件。使用-crc选项复制文件以及CRC信息。

示例：

```bash
hadoop fs -get /user/hadoop/file localfile
hadoop fs -get hdfs://host:port/user/hadoop/file localfile
```

&emsp;&emsp;返回值：

&emsp;&emsp;成功返回0，失败返回-1。

**getmerge**

&emsp;&emsp;使用方法：hadoop fs -getmerge <src> <localdst> [addnl]

&emsp;&emsp;接受一个源目录和一个目标文件作为输入，并且将源目录中所有的文件连接成本地目标文件。addnl是可选的，用于指定在每个文件结尾添加一个换行符。

**ls**

&emsp;&emsp;使用方法：hadoop fs -ls <args>

&emsp;&emsp;如果是文件，则按照如下格式返回文件信息：

&emsp;&emsp;文件名 <副本数> 文件大小 修改日期 修改时间 权限 用户ID 组ID 

&emsp;&emsp;如果是目录，则返回它直接子文件的一个列表，就像在Unix中一样。目录返回列表的信息如下：

&emsp;&emsp;目录名 <dir> 修改日期 修改时间 权限 用户ID 组ID 

&emsp;&emsp;示例：

```bash
hadoop fs -ls /user/hadoop/file1 /user/hadoop/file2 hdfs://host:port/user/hadoop/dir1 /nonexistentfile 
```

&emsp;&emsp;返回值：

&emsp;&emsp;成功返回0，失败返回-1。

 
**lsr**

&emsp;&emsp;使用方法：hadoop fs -lsr <args> 

&emsp;&emsp;ls命令的递归版本。类似于Unix中的ls -R。

**mkdir**

&emsp;&emsp;使用方法：hadoop fs -mkdir <paths> 

&emsp;&emsp;接受路径指定的uri作为参数，创建这些目录。其行为类似于Unix的mkdir -p，它会创建路径中的各级父目录。

&emsp;&emsp;示例：

```bash
hadoop fs -mkdir /user/hadoop/dir1 /user/hadoop/dir2
hadoop fs -mkdir hdfs://host1:port1/user/hadoop/dir hdfs://host2:port2/user/hadoop/dir
```

&emsp;&emsp;返回值：

&emsp;&emsp;成功返回0，失败返回-1。

**movefromLocal**

&emsp;&emsp;使用方法：dfs -moveFromLocal <src> <dst>

&emsp;&emsp;输出一个”not implemented“信息。

**mv**

&emsp;&emsp;使用方法：hadoop fs -mv URI [URI …] <dest>

&emsp;&emsp;将文件从源路径移动到目标路径。这个命令允许有多个源路径，此时目标路径必须是一个目录。不允许在不同的文件系统间移动文件。 

&emsp;&emsp;示例：

```bash
hadoop fs -mv /user/hadoop/file1 /user/hadoop/file2
hadoop fs -mv hdfs://host:port/file1 hdfs://host:port/file2 hdfs://host:port/file3 hdfs://host:port/dir1
```

&emsp;&emsp;返回值：

&emsp;&emsp;成功返回0，失败返回-1。

**put**

&emsp;&emsp;使用方法：hadoop fs -put <localsrc> ... <dst>

&emsp;&emsp;从本地文件系统中复制单个或多个源路径到目标文件系统。也支持从标准输入中读取输入写入目标文件系统。

```bash
hadoop fs -put localfile /user/hadoop/hadoopfile
hadoop fs -put localfile1 localfile2 /user/hadoop/hadoopdir
hadoop fs -put localfile hdfs://host:port/hadoop/hadoopfile
hadoop fs -put - hdfs://host:port/hadoop/hadoopfile 
```

&emsp;&emsp;从标准输入中读取输入。

&emsp;&emsp;返回值：

&emsp;&emsp;成功返回0，失败返回-1。

**rm**

&emsp;&emsp;使用方法：hadoop fs -rm URI [URI …]

&emsp;&emsp;删除指定的文件。只删除非空目录和文件。请参考rmr命令了解递归删除。

&emsp;&emsp;示例：

```bash
hadoop fs -rm hdfs://host:port/file /user/hadoop/emptydir
```

&emsp;&emsp;返回值：

&emsp;&emsp;成功返回0，失败返回-1。

**rmr**

&emsp;&emsp;使用方法：hadoop fs -rmr URI [URI …]

&emsp;&emsp;delete的递归版本。

&emsp;&emsp;示例：

```bash
hadoop fs -rmr /user/hadoop/dir
hadoop fs -rmr hdfs://host:port/user/hadoop/dir
```

&emsp;&emsp;返回值：

&emsp;&emsp;成功返回0，失败返回-1。

**setrep**

&emsp;&emsp;使用方法：hadoop fs -setrep [-R] <path>

&emsp;&emsp;改变一个文件的副本系数。-R选项用于递归改变目录下所有文件的副本系数。

&emsp;&emsp;示例：

```bash
hadoop fs -setrep -w 3 -R /user/hadoop/dir1
```

&emsp;&emsp;返回值：

&emsp;&emsp;成功返回0，失败返回-1。

**stat**

&emsp;&emsp;使用方法：hadoop fs -stat URI [URI …]

&emsp;&emsp;返回指定路径的统计信息。

&emsp;&emsp;示例：

```bash
hadoop fs -stat path
```

&emsp;&emsp;返回值：

&emsp;&emsp;成功返回0，失败返回-1。

**tail**

&emsp;&emsp;使用方法：hadoop fs -tail [-f] URI

&emsp;&emsp;将文件尾部1K字节的内容输出到stdout。支持-f选项，行为和Unix中一致。

&emsp;&emsp;示例：

```bash
hadoop fs -tail pathname
```

&emsp;&emsp;返回值：

&emsp;&emsp;成功返回0，失败返回-1。

**test**

&emsp;&emsp;使用方法：hadoop fs -test -[ezd] URI

&emsp;&emsp;选项：

&emsp;&emsp; -e 检查文件是否存在。如果存在则返回0。

&emsp;&emsp; -z 检查文件是否是0字节。如果是则返回0。 

&emsp;&emsp; -d 如果路径是个目录，则返回1，否则返回0。

&emsp;&emsp;示例：

```bash
hadoop fs -test -e filename
```

**text**

&emsp;&emsp;使用方法：hadoop fs -text <src> 

&emsp;&emsp;将源文件输出为文本格式。允许的格式是zip和TextRecordInputStream。

**touchz**

&emsp;&emsp;使用方法：hadoop fs -touchz URI [URI …] 

&emsp;&emsp;创建一个0字节的空文件。

&emsp;&emsp;示例：

```bash
hadoop -touchz pathname
```

&emsp;&emsp;返回值：

&emsp;&emsp;成功返回0，失败返回-1。