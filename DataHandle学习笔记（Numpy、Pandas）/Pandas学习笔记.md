# Pandas归纳

<br>
<br>


## 1. Pandas DataFrame基本操作

### 1.1 Pandas DataFrame基本信息

```python
#dataframe创建
s4 = pd.Series({"name": "nick", "age": 12, "sex": "male"})  # 通过dic创建Serise
 
d2 = pd.DataFrame(data=list([[1, 2, 3, 4], ["a", "b", "c", "d"]]))  # 通过list创建DataFrame
d3 = pd.DataFrame(data={"name": "nick", "age": 12, "sex": "male"}, index=list([1, 2, 3]))
d4 = pd.DataFrame(data={"A":{"name": "nick", "age": 12, "sex": "male"},"B":{"name": "nick", "age": 12, "sex": "male"}})
d5 = pd.DataFrame(data=s4)
series.to_frame(name = None)    # 将eries转换为DataFrame类型

# 指定dataframe数据类型
df = pd.DataFrame(a, dtype='float') #将所有数据设为同一类型
df = pd.DataFrame(a, columns = cols, dtype = {'col_name':str})  #对DataFrame中不同列设置不同的dtype

# 查看df信息
df.shape    # 显示df的shape信息
df.index    # 显示df的index
df.columns  # 显示df的columns
df.values   # 显示df中的值
df.head(n)  # 显示数据的前n行
df.tail(n)  # 显示数据的最后n行
```

<br>

### 1.2 Pandas DataFrame数据获取

```python
df.T    # df的转置

# 通过标签选择
df['A'] # df中A列的数据
df['20130102':'20130104']   #切片，在index为date类型的情况下，获取20130102-20130104（包含20140104）的行的所有数据
df.loc['20130102':'20130104', ['A', 'B']]   # 获取20130102-20130104行，A、B列的数据

# 通过位置选择
df.iloc[3:5, 0:2]   # 根据位置对数据切片
df.iloc[[1,2,4], [0,2]] # 根据位置获取对应位置数据
df.iloc[1:3, :] # 对行进行切片
df.iloc[:, 1:3] # 对列进行切片
df.iloc[1, 1]   # 获取特定位置的值

# 通过位置与标签选择
df.at['20130102', 'A'] # 结果同df.loc['20130102', 'A']，返回一个标量

# 数据过滤
df[df.A > 0]    # 使用一个单独的列值来过滤，输出df中A列值>0的所有行
df[df > 0]  # 使用where过滤，显示出df中>0的值，未>0的值为空(NaN)
df[df.A.isin(['two', 'four'])]  # 使用isin()方法过滤，选择满足条件的值
```

<br> 

### 1.3 Pandas DataFrame数据设置

```python

# 设置新的值
s1 = pd.Series([1, 2, 3, 4, 5, 6], index = pd.date_range('20130102', periods=6))
df['F'] = s1    # 设置新的列
df.at[dates[0], 'A']    # 通过标签设置新的值
df.iat[0, 1]    # 通过位置设置新的值
df.loc[:, 'D'] = np.array([5] * len(df))    # 通过一个numpy数组设置一组新值
df[df > 0] = -df    # 通过where操作设置新的值

# 缺失值处理
df.dropna(how = 'any')  # 去掉包含缺失值的行
df.fillna(value = 5)    # 对缺失值进行补充
pd.isnull(df)   # 对数据进行布尔填充
```

<br>

### 1.4 Pandas DataFrame数据操作

```python
# df设置小数点精度
df.round(2) # 设置df中小数点精度为2
df.round({'A': 1, 'C': 2})  # 设置df中A列小数点精度为1，C列中小数点精度为2

# df将小数转换为百分数
df['A'] = df['A'].apply(lambda x: format(x, '.2%')) # 将df中的A列的小数形式转换为百分数，注意此时A的类型为str

# stacked
stacked = df.stack()
stacked.unstack(1)

# 对数据进行操作变换

df.dropna(axis = 0, how = 'any', thresh = None, subset = None, inplace = False) # 删除df中为空的数据；axis = 0 or 1表示删除含有空值的行或列，how表示删除的方式，thresh表示限制非空数据的个数，subset表示寻找缺失值的咧，inplace=True表示不创建新的对象，直接对原始对象进行修改；inplace=False：对数据进行修改，创建并返回新的对象承载其修改结果。
df.shift(periods = 1, freq = None, axis = 0, fill_value = None) # shift函数可以把数据移动指定的位数，periods指移动的位数，axis指移动的轴，1为行，0为列；
df.rolling(window, min_periods=None, freq=None, center=False, win_type = None, axis=0, closed = None)
"""
    window：表示时间窗的大小，注意有两种形式（int or offset）。如果使用int，则数值表示计算统计量的观测值的数量即向前几个数据。如果是offset类型，表示时间窗的大小。
    min_period: 至少需要有值的观测点的数量，对于int类型，默认与window相等。对于offset类型，默认为1。
    freq：从0.18版本中已经被舍弃。
    center：是否使用window的中间值作为label，默认为false。只能在window是int时使用。
    win_type：窗口类型，默认为None，一般不特殊指定。
    on：对于DataFrame如果不使用index（索引）作为rolling的列，那么用on来指定使用哪列。
    closed：定义区间的开闭，曾经支持int类型的window，新版本已经不支持了。对于offset类型默认是左开右闭的即默认为right。可以根据情况指定为left both等。
    axis：方向（轴），一般都是0。
"""
df.diff(periods = 1, axis = 0)  # 计算一阶差分，periods:periods：移动的幅度，int类型，默认值为1；axis：移动的方向，{0 or ‘index’, 1 or ‘columns’}，如果为0或者’index’，则上下移动，如果为1或者’columns’，则左右移动。
df.rolling_count()   # 返回各窗口非NA观测值的量
df.rolling_sum() # 移动窗口的和
df.rolling_mean()    #移动窗口的平均值
df.rolling_median()  # 移动窗口的中位数
df.rolling_var()
df.rolling_std() # 移动窗口的方差和标准差。分母为n-1
df.rolling_skew()
df.rolling_kurt()   # 移动窗口的偏度（三阶矩）和峰度（四阶矩）
df.rolling_min()
df.rolling_max() # 移动窗口的最小值和最大值
df.rolling_quantile()    # 移动窗口指定百分位数/样本分位数位置的值
df.rolling_corr()
df.rolling_cov()    # 移动窗口的相关系数和协方差
df.rolling_apply()   # 对移动窗口应用普通数组函数
df.ewm(arg, com=None, span=None, halflife=None, alpha=None, min_periods=0, adjust=True, ignore_na=False, axis=0)    #com、span、halflife、alpha设定衰减系数的相关参数， min_periods最小窗口数，它以指数形式分配权重。
df.ewma(arg, com=None, span=None, halflife=None, min_periods=0, freq=None, adjust=True, how=None, ignore_na=False)    # 指数加权移动平均
df.ewmvar()
df.ewmstd()   # 指数加权移动方差和标准差
df.ewmcorr()
df.ewmcov   # 指数加权移动相关系数和协方差
```

<br>

### 1.5 pandas dataframe数据计算

```python
# 计算
df.mean()   # 对df的每一列求平均,默认为axis = 0
df.mean(1)  # 对df的每一行求平均
df.sub()
df.apply(np.cumsum)
df.apply(lambda x: x.max() - x.min())

series.value_counts()   #  形同word count，计算series中每个数的个数
series.str.lower()  # series对象在其str属性中配备了一组字符串处理方法，可以很容易的应用到数组中的每一个元素；

# grouping
df.groupby('A').sum()   # 按列A的数值求和
df.groupby(['A,B']).sum()   # 按列A、B的多层索引求和

# groupby与apply算法结合使用
# 获取每个元素在group中占比
def f(df):
    total = df['count'].sum()
    df['rate_sid'] = df['count'] / total
    return df

data_sid_groupby = total_data_df.groupby(['dim', 'period', 'sid']).apply(f)

# 生成透视表
pd.pivot_table(df, values='D', index=['A', 'B'], columns = ['C'])

```

<br>

### 1.6 pandas Categorical类型数据
```python
# 将A列数据转为category类型
df['A'] = df['A'].astype('category')    


# df 按指定的list排序
# df 按指定的list排序, 指定的list所包含元素和Dataframe中需要排序的列的元素一样多
order_list = ['d', 'c', 'b','a','e']
df['A'] = df['A'].astype('category')
df['A'].cat.reorder_categories(order_list, inplace = True)  # inplace = True，使 recorder_categories生效
df.sort_values('A', inplace = True)
# df 按指定的list排序, 指定的list所包含元素比Dataframe中需要排序的列的元素多
# 将上面的df.cat.reorder_categories() 改为df.cat.set_categories()
df['A'].cat.set_categories(list_custom_new, inplace = True)
# df 按指定的list排序, 指定的list所包含元素比Dataframe中需要排序的列的元素少
# 仍旧使用df.cat.set_categories()，order_list中不包含的元素记为0；
df['A'].cat.set_categories(list_custom_new, inplace = True)

```

<br>

### 1.7 Pandas DataFrame合并

```python
# df合并merge
pd.concat[[df1, df2, df3]]  # concat合并多个行
pd.merge(df1, df2, on='key')    # concat合并多个行
df.append(seris, ingore_index = True)   # 在df下添加一行
```

<br>

### 1.8 Pandas 时间日期处理

```python
# 转换string类型为日期类型数据
df.columns = ['date','number']
df['date'] = pd.to_datetime(df['date']) # 将数据类型转换为日期类型
df.index = pd.DatetimeIndex(data, copy=False, freq=None, start = None, periods = None, end = None, closed = None )   # 将df的index设为datetime类型


# 数据获取
df['2016':'2017']   # 获取2016至2017年的数据
df['2013-11']   # 获取某月的数据
df['2013-11-06':'2013-11-06']   #获取具体某天的数据，获取具体某天的数据，用datafrme直接选取某天时会报错，而series的数据就没有问题，可以考虑用区间来获取某天的数据。
# dataframe的truncate函数可以获取某个时期之前或之后的数据，或者某个时间区间的数据，但一般建议直接用切片（slice），这样更为直观，方便。
series.truncate(after = '2013-11')  # 获取某个时期之后的数据
series.truncate(before='2017-02')   # 获取某个时期之前的数据
df.index.weekday    # 只获取weekday数据

# 按年、月、日显示数据，但不统计
series.to_period('M')   # 按月显示，但不统计；请注意df.index的数据类型是DatetimeIndex，df_peirod的数据类型是PeriodIndex
series.to_period('Q')   # 按季度显示，但不统计
series.to_period('A')   # 按年度显示，但不统计
series.to_timestamp()   # 转换为时间戳

# 日期数据统计
df.groupby('weekday').aggregate(sum)    # 按星期统计数据和

# 创建时间段
date_range_ind = pd.date_range(start = '1/1/2012', end = '',  periods=100, freq='S')    # 创建20120101 00：00：00后的100个时期的日期，时期单位为秒；date可以换书写形式；类型为DateIndex
date_series = pd.Series(np.random.randint(0, 500, len(rng)), index = rng)   #以date_range_ind　为index，随机赋值
date_series.resample('5Min').sum() # 计算date_series前5min的数的和

# 时区表示
date_series_utc = date_series.tz_localize('UTC')    #  转换为UTC时区时间
date_series_utc.tz_convert('US/Eastern')    # 转换为时区时间
```

<br>

### 1.9 pandas 读取/存储数据：

```python
# df读取/写入csv
df = pd.read_csv(data_path, sep = '\t', header = 0)  
'''
pandas.read_csv(filepath_or_buffer, sep=', ', delimiter=None, header='infer', names=None, index_col=None, usecols=None, squeeze=False, prefix=None, mangle_dupe_cols=True, dtype=None, engine=None, converters=None, true_values=None, false_values=None, skipinitialspace=False, skiprows=None, nrows=None, na_values=None, keep_default_na=True, na_filter=True, verbose=False, skip_blank_lines=True, parse_dates=False, infer_datetime_format=False, keep_date_col=False, date_parser=None, dayfirst=False, iterator=False, chunksize=None, compression='infer', thousands=None, decimal=b'.', lineterminator=None, quotechar='"', quoting=0, escapechar=None, comment=None, encoding=None, dialect=None, tupleize_cols=None, error_bad_lines=True, warn_bad_lines=True, skipfooter=0, doublequote=True, delim_whitespace=False, low_memory=True, memory_map=False, float_precision=None)
params:
    filepath_or_buffer : str，pathlib。str, pathlib.Path, py._path.local.LocalPath or any object with a read() method (such as a file handle or StringIO);可以是URL，可用URL类型包括：http, ftp, s3和文件。对于多文件正在准备中;本地文件读取实例：://localhost/path/to/table.csv
    sep : str, default ‘,’;指定分隔符。如果不指定参数，则会尝试使用逗号分隔。分隔符长于一个字符并且不是‘\s+’,将使用python的语法分析器。并且忽略数据中的逗号。正则表达式例子：'\r\t'
    delimiter : str, default None;定界符，备选分隔符（如果指定该参数，则sep参数失效）
    delim_whitespace : boolean, default False.;指定空格(例如’ ‘或者’ ‘)是否作为分隔符使用，等效于设定sep='\s+'。如果这个参数设定为Ture那么delimiter 参数失效。在新版本0.18.1支持
    header : int or list of ints, default ‘infer’;指定行数用来作为列名，数据开始行数。如果文件中没有列名，则默认为0，否则设置为None。如果明确设定header=0 就会替换掉原来存在列名。header参数可以是一个list例如：[0,1,3]，这个list表示将文件中的这些行作为列标题（意味着每一列有多个标题），介于中间的行将被忽略掉（例如本例中的2；本例中的数据1,2,4行将被作为多级标题出现，第3行数据将被丢弃，dataframe的数据从第5行开始。）。注意：如果skip_blank_lines=True 那么header参数忽略注释行和空行，所以header=0表示第一行数据而不是文件的第一行。
    names : array-like, default None;用于结果的列名列表，如果数据文件中没有列标题行，就需要执行header=None。默认列表中不能出现重复，除非设定参数mangle_dupe_cols=True。
    index_col : int or sequence or False, default None;用作行索引的列编号或者列名，如果给定一个序列则有多个行索引。如果文件不规则，行尾有分隔符，则可以设定index_col=False 来是的pandas不适用第一列作为行索引。
    usecols : array-like, default None。返回一个数据子集，该列表中的值必须可以对应到文件中的位置（数字可以对应到指定的列）或者是字符传为文件中的列名。例如：usecols有效参数可能是 [0,1,2]或者是 [‘foo’, ‘bar’, ‘baz’]。使用这个参数可以加快加载速度并降低内存消耗。
    as_recarray : boolean, default False；不赞成使用：该参数会在未来版本移除。请使用pd.read_csv(...).to_records()替代。返回一个Numpy的recarray来替代DataFrame。如果该参数设定为True。将会优先squeeze参数使用。并且行索引将不再可用，索引列也将被忽略。
    squeeze : boolean, default False；如果文件值包含一列，则返回一个Series
    prefix : str, default None；在没有列标题时，给列添加前缀。例如：添加‘X’ 成为 X0, X1, ...
    mangle_dupe_cols : boolean, default True；重复的列，将‘X’...’X’表示为‘X.0’...’X.N’。如果设定为false则会将所有重名列覆盖。
    dtype : Type name or dict of column -> type, default None；每列数据的数据类型。例如 {‘a’: np.float64, ‘b’: np.int32}
    engine : {‘c’, ‘python’}, optional；Parser engine to use. The C engine is faster while the python engine is currently more feature-complete.使用的分析引擎。可以选择C或者是python。C引擎快但是Python引擎功能更加完备。
    converters : dict, default None；列转换函数的字典。key可以是列名或者列的序号。
    true_values : list, default None；Values to consider as True
    false_values : list, default None；Values to consider as False
    skipinitialspace : boolean, default False；忽略分隔符后的空白（默认为False，即不忽略）.
    skiprows : list-like or integer, default None；需要忽略的行数（从文件开始处算起），或需要跳过的行号列表（从0开始）。
    skipfooter : int, default 0；从文件尾部开始忽略。 (c引擎不支持)
    skip_footer : int, default 0；不推荐使用：建议使用skipfooter ，功能一样。
    nrows : int, default None；需要读取的行数（从文件头开始算起）。
    na_values : scalar, str, list-like, or dict, default None；一组用于替换NA/NaN的值。如果传参，需要制定特定列的空值。默认为‘1.#IND’, ‘1.#QNAN’, ‘N/A’, ‘NA’, ‘NULL’, ‘NaN’, ‘nan’`.
    keep_default_na : bool, default True；如果指定na_values参数，并且keep_default_na=False，那么默认的NaN将被覆盖，否则添加。
    na_filter : boolean, default True；是否检查丢失值（空字符串或者是空值）。对于大文件来说数据集中没有空值，设定na_filter=False可以提升读取速度。
    verbose : boolean, default False；是否打印各种解析器的输出信息，例如：“非数值列中缺失值的数量”等。
    skip_blank_lines : boolean, default True；如果为True，则跳过空行；否则记为NaN。
    parse_dates : boolean or list of ints or names or list of lists or dict, default False；boolean. True -> 解析索引；list of ints or names. e.g. If [1, 2, 3] -> 解析1,2,3列的值作为独立的日期列；list of lists. e.g. If [[1, 3]] -> 合并1,3列作为一个日期列使用；dict, e.g. {‘foo’ : [1, 3]} -> 将1,3列合并，并给合并后的列起名为"foo"
 
infer_datetime_format : boolean, default False
如果设定为True并且parse_dates 可用，那么pandas将尝试转换为日期类型，如果可以转换，转换方法并解析。在某些情况下会快5~10倍。
 
keep_date_col : boolean, default False
如果连接多列解析日期，则保持参与连接的列。默认为False。
 
date_parser : function, default None
用于解析日期的函数，默认使用dateutil.parser.parser来做转换。Pandas尝试使用三种不同的方式解析，如果遇到问题则使用下一种方式。
1.使用一个或者多个arrays（由parse_dates指定）作为参数；
2.连接指定多列字符串作为一个列作为参数；
3.每行调用一次date_parser函数来解析一个或者多个字符串（由parse_dates指定）作为参数。
 
dayfirst : boolean, default False
DD/MM格式的日期类型
 
iterator : boolean, default False
返回一个TextFileReader 对象，以便逐块处理文件。
 
chunksize : int, default None
文件块的大小， See IO Tools docs for more informationon iterator and chunksize.
 
compression : {‘infer’, ‘gzip’, ‘bz2’, ‘zip’, ‘xz’, None}, default ‘infer’
直接使用磁盘上的压缩文件。如果使用infer参数，则使用 gzip, bz2, zip或者解压文件名中以‘.gz’, ‘.bz2’, ‘.zip’, or ‘xz’这些为后缀的文件，否则不解压。如果使用zip，那么ZIP包中国必须只包含一个文件。设置为None则不解压。
新版本0.18.1版本支持zip和xz解压
 
thousands : str, default None
千分位分割符，如“，”或者“."
 
decimal : str, default ‘.’
字符中的小数点 (例如：欧洲数据使用’，‘).
 
float_precision : string, default None
Specifies which converter the C engine should use for floating-point values. The options are None for the ordinary converter, high for the high-precision converter, and round_trip for the round-trip converter.
指定
 
lineterminator : str (length 1), default None
行分割符，只在C解析器下使用。
 
quotechar : str (length 1), optional
引号，用作标识开始和解释的字符，引号内的分割符将被忽略。
 
quoting : int or csv.QUOTE_* instance, default 0
控制csv中的引号常量。可选 QUOTE_MINIMAL (0), QUOTE_ALL (1), QUOTE_NONNUMERIC (2) or QUOTE_NONE (3)
 
doublequote : boolean, default True
双引号，当单引号已经被定义，并且quoting 参数不是QUOTE_NONE的时候，使用双引号表示引号内的元素作为一个元素使用。
 
escapechar : str (length 1), default None
当quoting 为QUOTE_NONE时，指定一个字符使的不受分隔符限值。
 
comment : str, default None
标识着多余的行不被解析。如果该字符出现在行首，这一行将被全部忽略。这个参数只能是一个字符，空行（就像skip_blank_lines=True）注释行被header和skiprows忽略一样。例如如果指定comment='#' 解析‘#empty\na,b,c\n1,2,3’ 以header=0 那么返回结果将是以’a,b,c'作为header。
 
encoding : str, default None
指定字符集类型，通常指定为'utf-8'. List of Python standard encodings
 
dialect : str or csv.Dialect instance, default None
如果没有指定特定的语言，如果sep大于一个字符则忽略。具体查看csv.Dialect 文档
 
tupleize_cols : boolean, default False
Leave a list of tuples on columns as is (default is to convert to a Multi Index on the columns)
 
error_bad_lines : boolean, default True
如果一行包含太多的列，那么默认不会返回DataFrame ，如果设置成false，那么会将改行剔除（只能在C解析器下使用）。
 
warn_bad_lines : boolean, default True
如果error_bad_lines =False，并且warn_bad_lines =True 那么所有的“bad lines”将会被输出（只能在C解析器下使用）。
 
low_memory : boolean, default True
分块加载到内存，再低内存消耗中解析。但是可能出现类型混淆。确保类型不被混淆需要设置为False。或者使用dtype 参数指定类型。注意使用chunksize 或者iterator 参数分块读入会将整个文件读入到一个Dataframe，而忽略类型（只能在C解析器中有效）
 
buffer_lines : int, default None
不推荐使用，这个参数将会在未来版本移除，因为他的值在解析器中不推荐使用
 
compact_ints : boolean, default False
不推荐使用，这个参数将会在未来版本移除
如果设置compact_ints=True ，那么任何有整数类型构成的列将被按照最小的整数类型存储，是否有符号将取决于use_unsigned 参数
 
use_unsigned : boolean, default False
不推荐使用：这个参数将会在未来版本移除
如果整数列被压缩(i.e. compact_ints=True)，指定被压缩的列是有符号还是无符号的。
memory_map : boolean, default False
如果使用的文件在内存内，那么直接map文件使用。使用这种方式可以避免文件再次进行IO操作。
'''
df.to_csv(save_path, encoding = 'gb2312')

# df读取/写入hdf5
df = pd.read_hdf('foo.h5', 'df')
df.to_hdf(save_path, 'df')

# df读取/写入excel文件
df = pd.read_excel(data_path, 'sheet', index_col = None, na_values = ['NA'])
df.to_excel(save_path, sheet_name = 'sheet')
```


<br>
<br>

## 2. Pandas DataFrame操作示范

### 2.1 Pandas DataFrame排序

```python
# df排序
df.sort_index(axis=1, ascending=False) # dataframe根据列索引(axis = 0 或者省略时表示根据行索引)进行降序排序（排序时默认升序，调节ascending参数）
df.sort_values(by='a') # dataframe根据值进行排序
df.sort_values(by=['a','c'])   # 通过多个索引进行排序
# df 按指定的list排序, 指定的list所包含元素和Dataframe中需要排序的列的元素一样多
order_list = ['d', 'c', 'b','a','e']
df['A'] = df['A'].astype('category')
df['A'].cat.reorder_categories(order_list, inplace = True)  # inplace = True，使 recorder_categories生效
df.sort_values('A', inplace = True)
# df 按指定的list排序, 指定的list所包含元素比Dataframe中需要排序的列的元素多
# 将上面的df.cat.reorder_categories() 改为df.cat.set_categories()
df['A'].cat.set_categories(list_custom_new, inplace = True)
# df 按指定的list排序, 指定的list所包含元素比Dataframe中需要排序的列的元素少
# 仍旧使用df.cat.set_categories()，order_list中不包含的元素记为0；
df['A'].cat.set_categories(list_custom_new, inplace = True)
```

<br>

### 2.2 DataFrame的遍历

```python
# 遍历dataframe中的行
# 方法一
for index, row in df.iterrows():
    print row["c1"], row["c2"]  
# 方法二
for row in df.itertuples(index=True, name='Pandas'):
# 方法三
for i in range(0, len(df)):
    print df.iloc[i]['c1'], df.iloc[i]['c2']
    
# 遍历dataframe中的列
for ix, col in df.iteritems():
    print()

```

### 2.3 DataFrame列与索引之间的相互转化

```python
# 列转化为索引：
df.set_index('c1')  # 将c1列作为索引
df.set_index(['c1', 'c2'])  #指定c1、c2列作为多级索引，其中c1列为一级索引
df.set_index(['c1', 'c2'], drop=False)  #同时保留作为索引的列

# 索引转化为列
df.reset_index('index1', )    #将index1索引作为列
df.reset_index()    #将df中的多级索引转换为列
df.reset_index('index1', drop = True)   #直接删除索引index1
df.reset_index(inplace=True)    # 直接将原dataframe对象df中索引转为列

# 设置多层索引
index = pd.MultiIndex.from_tuples(tuples, names=['first', 'second'])
df = pd.DataFrame(np.random.randn(8, 2), index, columns=['A', 'B'])
```

### 2.4 








## Reference：

1. [十分钟搞定Pandas](http://docs.bdpt.net/docs/pandastutorialcn/en/latest/10.html)

2. [Pandas秘籍](http://docs.bdpt.net/docs/pandastutorialcn/en/latest/21.html)

3. [Pandas新手入门教程](http://docs.bdpt.net/docs/pandastutorialcn/en/latest/31.html)

4. [pandas.read_csv()](https://pandas.pydata.org/pandas-docs/stable/generated/pandas.read_csv.html)

5. [Python： Pandas的DataFrame如何按指定list排序](https://www.cnblogs.com/lemonbit/p/7004505.html)

6. [Pandas Data Visualisation](https://www.kaggle.com/learn/data-visualisation)

7. [pandas中时间窗函数rolling的使用](https://blog.csdn.net/wj1066/article/details/78853717)

8. [pandas DataFrame.shift()函数](http://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.DataFrame.shift.html)