# Hive学习笔记（HQL语言）

<br>
<br>
<br>
<br>

## 1 Hive对数据库的操作

### 1.1 Hive对TABLE的操作

### 1.1.1 CREATE TABLE语句

**语法**

```
CREATE [TEMPORARY] [EXTERNAL] TABLE [IF NOT EXISTS] [db_name.] table_name

[(col_name data_type [COMMENT col_comment], ...)]
[COMMENT table_comment]
[ROW FORMAT row_format]
[STORED AS file_format]

```

**示例**

```
CREATE TABLE IF NOT EXISTS employee ( eid int, name String,
salary String, destination String)
COMMENT ‘Employee details’
ROW FORMAT DELIMITED
FIELDS TERMINATED BY ‘\t’
LINES TERMINATED BY ‘\n’
STORED AS TEXTFILE;
```

### 1.1.2 ALTER TABLE 语句

**语法**

```
ALTER TABLE name RENAME TO new_name
ALTER TABLE name ADD COLUMNS (col_spec[, col_spec ...])
ALTER TABLE name DROP [COLUMN] column_name
ALTER TABLE name CHANGE column_name new_name new_type
ALTER TABLE name REPLACE COLUMNS (col_spec[, col_spec ...])
```

**示例**

```
ALTER TABLE employee RENAME TO emp;
```

### 1.1.3 DROP TABLE 语句

**语法**

```
DROP TABLE [IF EXISTS] table_name;
```

**示例**

```
DROP TABLE IF EXISTS employee;
```

### 1.2 Hive对TABLE中数据的操作

#### 1.2.1 SELECT

#### 1.2.2 Hive中的通配符

&emsp;&emsp;Hive中有两个用于通配的操作符，LIKE和RLIKE。
    
##### 1.2.2.1 LIKE

&emsp;&emsp;语法格式为:

```sql
A [NOT] LIKE B
```

&emsp;&emsp;B是sql下的简单正则表达式，也叫通配符模式，如"_"匹配一个字符，"%"可以匹配任意多个字符，A会对表达式B做匹配，如果通过返回TRUE，如果不通过则返回FALSE，举个栗子 

&emsp;&emsp;举几个例子：



```sql
SELECT name LIKE '%Alice' FROM table1 -- 选择name列内以ALICE作为结尾的数据。

A LIKE '%Alice%' OR A LIKE '%Ben%'  -- 匹配包含Alice或者Ben的字段
```


###### 1.2.2.2 RLIKE

&emsp;&emsp;语法格式为

```sql
A [NOT] RLIKE B
```

&emsp;&emsp;基于java的正则表达式接口实现，如果A中有与B匹配则返回TRUE，否则返回FALSE

```sql
A RLIKE '.*(Alice|Ben).*'  -- 匹配包含Alice或者Ben的字段
```

&emsp;&emsp;RLIKE基于java的正则表达式接口实现，直接看Java的正则表达式语法：

|字符|说明|
|:--|:--|
|"\"|将下一字符标记为特殊字符、文本、反向引用或八进制转义符。例如，"n"匹配字符"n"。"\n"匹配换行符。序列"\\\\"匹配"\\"，"\\("匹配"("。|
|^|匹配输入字符串开始的位置。|
|$|匹配输入字符串结尾的位置。|
|*|零次或多次匹配前面的字符或子表达式。例如，zo* 匹配"z"和"zoo"。* 等效于 {0,}。|
|+|一次或多次匹配前面的字符或子表达式。例如，"zo+"与"zo"和"zoo"匹配，但与"z"不匹配。+ 等效于 {1,}。|
|?|零次或一次匹配前面的字符或子表达式。例如，"do(es)?"匹配"do"或"does"中的"do"。? 等效于 {0,1}。|
|{n}|n 是非负整数。正好匹配 n 次。例如，"o{2}"与"Bob"中的"o"不匹配，但与"food"中的两个"o"匹配。|
|{n,}|n 是非负整数。至少匹配 n 次。例如，"o{2,}"不匹配"Bob"中的"o"，而匹配"foooood"中的所有 o。"o{1,}"等效于"o+"。"o{0,}"等效于"o*"。|
|{n,m}|m 和 n 是非负整数，其中 n <= m。匹配至少 n 次，至多 m 次。例如，"o{1,3}"匹配"fooooood"中的头三个 o。'o{0,1}' 等效于 'o?'。注意：您不能将空格插入逗号和数字之间。|
|?|当此字符紧随任何其他限定符（*、+、?、{n}、{n,}、{n,m}）之后时，匹配模式是"非贪心的"。"非贪心的"模式匹配搜索到的、尽可能短的字符串，而默认的"贪心的"模式匹配搜索到的、尽可能长的字符串。例如，在字符串"oooo"中，"o+?"只匹配单个"o"，而"o+"匹配所有"o"。|
|.|匹配除"\r\n"之外的任何单个字符。若要匹配包括"\r\n"在内的任意字符，请使用诸如"[\s\S]"之类的模式。|
|(pattern)|匹配 pattern 并捕获该匹配的子表达式。可以使用 $0…$9 属性从结果"匹配"集合中检索捕获的匹配。若要匹配括号字符 ( )，请使用"\("或者"\)"。|
|(?:pattern)|匹配 pattern 但不捕获该匹配的子表达式，即它是一个非捕获匹配，不存储供以后使用的匹配。这对于用"or"字符 (|) 组合模式部件的情况很有用。例如，'industr(?:y|ies) 是比 'industry|industries' 更经济的表达式。|
|(?=pattern)|执行正向预测先行搜索的子表达式，该表达式匹配处于匹配 pattern 的字符串的起始点的字符串。它是一个非捕获匹配，即不能捕获供以后使用的匹配。例如，'Windows (?=95|98|NT|2000)' 匹配"Windows 2000"中的"Windows"，但不匹配"Windows 3.1"中的"Windows"。预测先行不占用字符，即发生匹配后，下一匹配的搜索紧随上一匹配之后，而不是在组成预测先行的字符后。|
|(?!pattern)|执行反向预测先行搜索的子表达式，该表达式匹配不处于匹配 pattern 的字符串的起始点的搜索字符串。它是一个非捕获匹配，即不能捕获供以后使用的匹配。例如，'Windows (?!95|98|NT|2000)' 匹配"Windows 3.1"中的 "Windows"，但不匹配"Windows 2000"中的"Windows"。预测先行不占用字符，即发生匹配后，下一匹配的搜索紧随上一匹配之后，而不是在组成预测先行的字符后。|
|x|y|匹配 x 或 y。例如，'z|food' 匹配"z"或"food"。'(z|f)ood' 匹配"zood"或"food"。|
|[xyz]|字符集。匹配包含的任一字符。例如，"[abc]"匹配"plain"中的"a"。|
|[^xyz]|反向字符集。匹配未包含的任何字符。例如，"[^abc]"匹配"plain"中"p"，"l"，"i"，"n"。|
|[a-z]|字符范围。匹配指定范围内的任何字符。例如，"[a-z]"匹配"a"到"z"范围内的任何小写字母。|
|[^a-z]|反向范围字符。匹配不在指定的范围内的任何字符。例如，"[^a-z]"匹配任何不在"a"到"z"范围内的任何字符。|
|\b|匹配一个字边界，即字与空格间的位置。例如，"er\b"匹配"never"中的"er"，但不匹配"verb"中的"er"。|
|\B|非字边界匹配。"er\B"匹配"verb"中的"er"，但不匹配"never"中的"er"。|
|\cx|匹配 x 指示的控制字符。例如，\cM 匹配 Control-M 或回车符。x 的值必须在 A-Z 或 a-z 之间。如果不是这样，则假定 c 就是"c"字符本身。|
|\d|数字字符匹配。等效于 [0-9]。|
|\D|非数字字符匹配。等效于 [^0-9]。|
|\f|换页符匹配。等效于 \x0c 和 \cL。|
|\n|换行符匹配。等效于 \x0a 和 \cJ。|
|\r|匹配一个回车符。等效于 \x0d 和 \cM。|
|\s|匹配任何空白字符，包括空格、制表符、换页符等。与 [ \f\n\r\t\v] 等效。|
|\S|匹配任何非空白字符。与 [^ \f\n\r\t\v] 等效。|
|\t|制表符匹配。与 \x09 和 \cI 等效。|
|\v|垂直制表符匹配。与 \x0b 和 \cK 等效。|
|\w|匹配任何字类字符，包括下划线。与"[A-Za-z0-9_]"等效。|
|\W|与任何非单词字符匹配。与"[^A-Za-z0-9_]"等效。|
|\xn|匹配 n，此处的 n 是一个十六进制转义码。十六进制转义码必须正好是两位数长。例如，"\x41"匹配"A"。"\x041"与"\x04"&"1"等效。允许在正则表达式中使用 ASCII 代码。|
|\num|匹配 num，此处的 num 是一个正整数。到捕获匹配的反向引用。例如，"(.)\1"匹配两个连续的相同字符。|
|\n|标识一个八进制转义码或反向引用。如果 \n 前面至少有 n 个捕获子表达式，那么 n 是反向引用。否则，如果 n 是八进制数 (0-7)，那么 n 是八进制转义码。|
|\nm|标识一个八进制转义码或反向引用。如果 \nm 前面至少有 nm 个捕获子表达式，那么 nm 是反向引用。如果 \nm 前面至少有 n 个捕获，则 n 是反向引用，后面跟有字符 m。如果两种前面的情况都不存在，则 \nm 匹配八进制值 nm，其中 n 和 m 是八进制数字 (0-7)。|
|\nml|当 n 是八进制数 (0-3)，m 和 l 是八进制数 (0-7) 时，匹配八进制转义码 nml。|
|\un|匹配 n，其中 n 是以四位十六进制数表示的 Unicode 字符。例如，\u00A9 匹配版权符号 (©)。|


<br>
<br>

## 2 Hive 数据导入导出

### 2.1 Hive数据导入

```bash
hive> load data local inpath 'wyp.txt' into table wyp; -- 从本地文件系统中导入数据到Hive表

hive> load data inpath '/home/wyp/add.txt' into table wyp; -- HDFS上导入数据到Hive表

hive> insert into table test
    > partition (age='25')
    > select id, name, tel
    > from wyp; -- 从别的表中查询出相应的数据并导入到Hive表中
    
hive> create table test4
    > as
    > select id, name, tel
    > from wyp; -- 在创建表的时候通过从别的表中查询出相应的记录并插入到所创建的表中

```

> 和我们熟悉的关系型数据库不一样，Hive现在还不支持在insert语句里面直接给出一组记录的文字形式，也就是说，Hive并不支持INSERT INTO .... VALUES形式的语句。

### 2.2 Hive数据导出


```bash
hive> insert overwrite local directory '/home/iteblog/local'
    > row format delimited
    > fields terminated by '\t'
    > select * from wyp;    -- 导出到本地文件系统
    
hive> insert overwrite directory '/home/wyp/hdfs'
    > select * from wyp;    -- 导出到hdfs
   
hive> insert into table test
    > partition (age='25')
    > select id, name, tel
    > from wyp;     -- 导出到Hive的另一个表中

```



<br>
<br>
<br>
<br>

## Reference:

1. [HIVE中LIKE和RLIKE的区别](https://blog.csdn.net/u013019431/article/details/78491037)

2. [Java 正则表达式](http://www.runoob.com/java/java-regular-expressions.html)

3. [Hive的几种数据导入方式](https://www.iteblog.com/archives/949.html)

4.[Hive几种数据导出方式](https://www.iteblog.com/archives/955.html)

