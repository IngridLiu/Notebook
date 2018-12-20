# SQL中的其他函数

<br>
<br>

## SQL中的cast()函数

**语法：**

```sql
CAST (expression AS data_type)
```

**参数说明：**

- expression：任何有效的SQServer表达式。

- AS：用于分隔两个参数，在AS之前的是要处理的数据，在AS之后是要转换的数据类型。

- data_type：目标系统所提供的数据类型，包括bigint和sql_variant，不能使用用户定义的数据类型。

使用CAST函数进行数据类型转换时，在下列情况下能够被接受：

（1）两个表达式的数据类型完全相同。
（2）两个表达式可隐性转换。
（3）必须显式转换数据类型。

如果试图进行不可能的转换（例如，将含有字母的 char 表达式转换为 int 类型），SQServer 将显示一条错误信息。

## SQL中的CONCAT()函数

**示例：**

```sql
SELECT CONCAT('FIRST ', 'SECOND');
-- return: 'FIRST SECOND'

SELECT CONCAT(id, name, date) FROM table;
-- 示例 return: 1John2007-01-24
```
