# Python与MySQL中Errors集合

<br>
<br>
<br>
<br>

## 1 Error:Process finished with exit code 139 (interrupted by signal 11: SIGSEGV)

&emsp;&emsp;使用python连接mysql数据库，向数据库中insert数据，运行报错，无法正常运行python程序，获得的报错信息如下:

&emsp;&emsp;Process finished with exit code 139 (interrupted by signal 11: SIGSEGV)

&emsp;&emsp;查阅是内存异常，怀疑是同时处理了较多insert命令.

&emsp;&emsp;修改方法：将所有的insert合并为一条insert命令，批量插入数据。

<br>

## 2. Error Code: 1292. Incorrect date value: 1998-01-01 for column 'date' at row 1

&emsp;&emsp;使用python连接mysql数据库，向数据库中insert数据，运行报错，无法正常运行python程序，获得的报错信息如下:

&emsp;&emsp;Error Code: 1292. Incorrect date value: 1998-01-01 for column 'date' at row 1

&emsp;&emsp;查阅是date日期型数据格式不对，此处写法正确，格式不对之处在未加上单引号''

&emsp;&emsp;修改方法：将1998-01-01修改为'1998-01-01'。

<br>

## 3 Error:MySQL error #1054 - Unknown column in 'Field List'

&emsp;&emsp;使用python连接mysql数据库，向数据库中insert数据，运行报错，无法正常运行python程序，获得的报错信息如下:

&emsp;&emsp;Error:MySQL error #1054 - Unknown column in 'Field List'

&emsp;&emsp;无法找到对应列，检查代码列值对应关系正确，而错误是由insert数据格式引起，应该将所有的字符串类型的值加上单引号''

&emsp;&emsp;修改方法：将insert数据中所有的str型数据都加上单引号''。
