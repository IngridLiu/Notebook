# pandas.DataFrame
<br>
<br>
<br>


## 1 DataFrame.from_dict()
&emsp;&emsp;classmethod DataFrame.from_dict(data, orient='columns', dtype=None)
&emsp;&emsp;[]()
### 1.1 描述
&emsp;&emsp;Construct DataFrame from dict of array-like or dicts
### 1.2 参数描述
&emsp;&emsp;classmethod DataFrame.from_dict(data, orient='columns', dtype=None)
**Parameters：**
&emsp;&emsp;- data:dict
&emsp;&emsp;&emsp;&emsp;{field : array-like} or {field : dict}
&emsp;&emsp;- orient:
&emsp;&emsp;&emsp;&emsp;{‘columns’, ‘index’}, default ‘columns’
&emsp;&emsp;The “orientation” of the data. If the keys of the passed dict should be the columns of the resulting DataFrame, pass ‘columns’ (default). Otherwise if the keys should be rows, pass ‘index’.
&emsp;&emsp;- dtype: dtype, default None
&emsp;&emsp;&emsp;&emsp;Data type to force, otherwise infer
**Returns：**
&emsp;&emsp;DataFrame
<br>