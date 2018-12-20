# Hive中其他函数

<br>
<br>

## 1. Hive中split函数

**语法: **

```sql
split(string str, string pat) 
```

返回值: array
 
说明: 按照pat字符串分割str，会返回分割后的字符串数组 

**示例**:

```sql
-- 基本用法
select split('abcdef', 'c') from test;
-- return: ["ab", "def"]

-- 截取字符串中的某个值
select split('abcdef', 'c')[0] from test;
-- return: ab

-- 特殊字符 
-- 如正则表达式中的特殊符号作为分隔符时，需做转义 (前缀加上\)

select split('ab_cd_ef', '\_')[0] from test;
-- return: ab
```