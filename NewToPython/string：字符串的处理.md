# String：字符串的处理

## 1 字符串的格式化

### 1.1使用format()格式化字符串
```
'{0}, {1}, {2}'.format('a', 'b', 'c')
#'a, b, c'
'{}, {}, {}'.format('a', 'b', 'c')  # 3.1+ only
#'a, b, c'
'{2}, {1}, {0}'.format('a', 'b', 'c')
#'c, b, a'
'{2}, {1}, {0}'.format(*'abc')      # unpacking argument sequence
#'c, b, a'
'{0}{1}{0}'.format('abra', 'cad')   # arguments' indices can be repeated
#'abracadabra'

```