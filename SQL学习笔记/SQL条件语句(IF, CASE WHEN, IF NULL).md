# SQL条件语句(IF, CASE WHEN, IF NULL)

<br>
<br>
<br>
<br>

## 1.IF

表达式：IF( expr1 , expr2 , expr3 )

expr1条件，条件为true，则值是expr2 ，false，值就是expr3 

```sql
SELECT 
o.id,u.account,catagory.`name`,orderTime,detail.amount,periodtime,if(direction='0','看涨','看跌') directionName
FROM t_order_detail detail
LEFT JOIN t_order o ON o.id = detail.orderId
LEFT JOIN t_catagory catagory ON catagory.id = o.catId
LEFT JOIN t_user u ON u.id = o.userId
```

## 2. CASE WHEN

表达式：

CASE 列名

    WHEN 条件 THEN 结果
    
    ELSE 其他结果
    
    END 别名
    
例子：

```sql
SELECT 
CASE detail.`status` WHEN '0' THEN '未开仓'
WHEN '1' THEN '已开仓'
WHEN '2' THEN '已平仓'
ELSE '取消订单' END
status,
CASE o.type WHEN '0' THEN '单期'
WHEN '1' THEN '多期'
ELSE '策略' END 
typeName
FROM t_order_detail detail
LEFT JOIN t_order o ON o.id = detail.orderId
```

## 3. IFNULL

表达式：IFNULL( expr1 , expr2)

在 expr1 的值不为 NULL的情况下都返回 expr1，否则返回 expr2

```sql
select IFNULL(detailcode,'无') detailcode from ...
```