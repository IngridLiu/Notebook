# MySQL有多种存储引擎

<br>
<br>

## 1. MySQL的存储引擎

MySQL有多种存储引擎，每种存储引擎有各自的优缺点，可以择优选择使用： 

MyISAM、InnoDB、MERGE、MEMORY(HEAP)、BDB(BerkeleyDB)、EXAMPLE、FEDERATED、ARCHIVE、CSV、BLACKHOLE。 

MySQL支持数个存储引擎作为对不同表的类型的处理器。MySQL存储引擎包括处理事务安全表的引擎和处理非事务安全表的引擎： 

· MyISAM管理非事务表。它提供高速存储和检索，以及全文搜索能力。MyISAM在所有MySQL配置里被支持，它是默认的存储引擎，除非你配置MySQL默认使用另外一个引擎。 

· MEMORY存储引擎提供“内存中”表。MERGE存储引擎允许集合将被处理同样的MyISAM表作为一个单独的表。就像MyISAM一样，MEMORY和MERGE存储引擎处理非事务表，这两个引擎也都被默认包含在MySQL中。 

注释：MEMORY存储引擎正式地被确定为HEAP引擎。 

· InnoDB和BDB存储引擎提供事务安全表。BDB被包含在为支持它的操作系统发布的MySQL-Max二进制分发版里。InnoDB也默认被包括在所 有MySQL 5.1二进制分发版里，你可以按照喜好通过配置MySQL来允许或禁止任一引擎。 

· EXAMPLE存储引擎是一个“存根”引擎，它不做什么。你可以用这个引擎创建表，但没有数据被存储于其中或从其中检索。这个引擎的目的是服务，在 MySQL源代码中的一个例子，它演示说明如何开始编写新存储引擎。同样，它的主要兴趣是对开发者。 

· NDB Cluster是被MySQL Cluster用来实现分割到多台计算机上的表的存储引擎。它在MySQL-Max 5.1二进制分发版里提供。这个存储引擎当前只被Linux, Solaris, 和Mac OS X 支持。在未来的MySQL分发版中，我们想要添加其它平台对这个引擎的支持，包括Windows。 

· ARCHIVE存储引擎被用来无索引地，非常小地覆盖存储的大量数据。 

· CSV存储引擎把数据以逗号分隔的格式存储在文本文件中。 

· BLACKHOLE存储引擎接受但不存储数据，并且检索总是返回一个空集。 

· FEDERATED存储引擎把数据存在远程数据库中。在MySQL 5.1中，它只和MySQL一起工作，使用MySQL C Client API。在未来的分发版中，我们想要让它使用其它驱动器或客户端连接方法连接到另外的数据源。


## 2. MyISAM和InnoBD

比较常用的是MyISAM和InnoBD

|     | MyISAM | InnoDB |
|:----|:-------|:-------|
|构成上的区别:|每个MyISAM在磁盘上存储成三个文件。第一个文件的名字以表的名字开始，扩展名指出文件类型。<br>.frm文件存储表定义。<br>数据文件的扩展名为.MYD (MYData)。<br>索引文件的扩展名是.MYI (MYIndex)。|基于磁盘的资源是InnoDB表空间数据文件和它的日志文件，InnoDB 表的大小只受限于操作系统文件的大小，一般为 2GB|
|事务处理上方面 : |MyISAM类型的表强调的是性能，其执行数度比InnoDB类型更快，但是不提供事务支持|InnoDB提供事务支持事务，外部键（foreign key）等高级数据库功能|
|SELECT   UPDATE,INSERT ， Delete 操作 |如果执行大量的SELECT，MyISAM是更好的选择|1.如果你的数据执行大量的INSERT 或 UPDATE，出于性能方面的考虑，应该使用InnoDB表<br>2.DELETE   FROM table时，InnoDB不会重新建立表，而是一行一行的删除。<br>3.LOAD   TABLE FROM MASTER操作对InnoDB是不起作用的，解决方法是首先把InnoDB表改成MyISAM表，导入数据后再改成InnoDB表，但是对于使用的额外的InnoDB特性（例如外键）的表不适用|
|对 AUTO_INCREMENT 的操作 |每表一个AUTO_INCREMEN列的内部处理。<br> MyISAM 为 INSERT 和 UPDATE 操作自动更新这一列。这使得AUTO_INCREMENT列更快（至少10%）。在序列顶的值被删除之后就不能再利用。(当AUTO_INCREMENT列被定义为多列索引的最后一列，可以出现重使用从序列顶部删除的值的情况）。<br>AUTO_INCREMENT值可用ALTER TABLE或myisamch来重置。<br>对于AUTO_INCREMENT类型的字段，InnoDB中必须包含只有该字段的索引，但是在MyISAM表中，可以和其他字段一起建立联合索引。更好和更快的auto_increment处理|如果你为一个表指定AUTO_INCREMENT列，在数据词典里的InnoDB表句柄包含一个名为自动增长计数器的计数器，它被用在为该列赋新值。<br>自动增长计数器仅被存储在主内存中，而不是存在磁盘上,关于该计算器的算法实现，请参考。AUTO_INCREMENT 列在 InnoDB 里如何工作 。|
|表的具体行数|select count(*) from table,MyISAM只要简单的读出保存好的行数，注意的是，当count(*)语句包含   where条件时，两种表的操作是一样的|InnoDB 中不保存表的具体行数，也就是说，执行select count(*) from table时，InnoDB要扫描一遍整个表来计算有多少行|
|锁|表锁|提供行锁(locking on row level)，提供与 Oracle 类型一致的不加锁读取(non-locking read in SELECTs)，另外，InnoDB表的行锁也不是绝对的，如果在执行一个SQL语句时MySQL不能确定要扫描的范围，InnoDB表同样会锁全表， 例如update table set num=1 where name like “%aaa%”|


  
  
  	  

  	  
  
   

  
  	  

  

  	  

  自动增长计数器仅被存储在主内存中，而不是存在磁盘上

  关于该计算器的算法实现，请参考

  AUTO_INCREMENT 列在 InnoDB 里如何工作 

  
  表的具体行数 
  	  select count(*) from table,MyISAM只要简单的读出保存好的行数，注意的是，当count(*)语句包含   where条件时，两种表的操作是一样的

  	  InnoDB 中不保存表的具体行数，也就是说，执行select count(*) from table时，InnoDB要扫描一遍整个表来计算有多少行

  
  锁 
  	  表锁

  	  提供行锁(locking on row level)，提供与 Oracle 类型一致的不加锁读取(non-locking read in
   SELECTs)，另外，InnoDB表的行锁也不是绝对的，如果在执行一个SQL语句时MySQL不能确定要扫描的范围，InnoDB表同样会锁全表， 例如update table set num=1 where name like “%aaa%”