# Mac相关问题

<br>
<br>

1. 关于MAC系统没有修改系统文件权限问题

&emsp;&emsp;在Mac中发现系统管理员也没有权限对系统文件进行写操作，发现是由于系统启用了SIP（System Integerity Protection）导致root用户也没有修改权限，所以我们需要屏蔽掉这个功能，具体做法是：

（1）重启电脑

（2）command + R 进入recover模式

（3）点击最上方菜单使用工具，选择终端

（4）运行命令csrutil disable

（5）当出现successfully字样，代表关闭成功！




<br>
<br>
<br>
<br>

## Reference:

1. [关于MAC系统没有修改/usr/bin和/usr/sbin文件夹权限问题](https://blog.csdn.net/a547720714/article/details/52678643)