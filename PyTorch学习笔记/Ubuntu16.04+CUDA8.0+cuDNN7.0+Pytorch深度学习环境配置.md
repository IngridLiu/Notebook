# Ubuntu16.04+CUDA8.0+cuDNN7.0+Pytorch深度学习环境配置

<br>
<br>

## 1. 准备工作

(1) 首先是检查GPU是否支持CUDA，在终端输入：

```bash
lspci | grep -i nvidia
```

(2) 进入bias，关闭安全启动模式

(3) 下载准备：

&emsp;&emsp;对应自己的显卡型号和系统下载好相应的显卡驱动、CUDA、cuDNN以及Anaconda，为了安装方便，显卡驱动和CUDA选择run文件的方式，下载CUDA的时候记得把后边的补丁文件一起都下载下来。下载cuDNN会要求你注册一个账号，过程很简单。

**下载显卡驱动：**

[显卡驱动下载地址](http://www.nvidia.cn/Download/index.aspx?lang=cn)

&emsp;&emsp;选择自己显卡型号对应的显卡驱动，我的显卡是GeForce GTX 1050；

![](https://pic4.zhimg.com/80/v2-3bf27d0db318770d32f275e2135acfff_hd.jpg)

**cuda下载：**

[CUDA下载地址](https://developer.nvidia.com/cuda-downloads)

[早期版本CUDA下载地址](https://developer.nvidia.com/cuda-toolkit-archive)

&emsp;&emsp;目前cuda已到cuda 10版本，之前安装为cuda8.0版本，此处依旧使用cuda8.0版本。

**cudnn下载**

[cuDNN下载地址](https://developer.nvidia.com/cudnn)

&emsp;&emsp;目前根据cuda版本选择对应的cudnn版本，cuda8.0对应的最新版本的cudnn为cudnn7。

<br>

## 2. 安装显卡驱动

(1) 禁用显卡驱动nouveau

&emsp;&emsp;Ubuntu自带的显卡驱动叫做nouveau，安装我们需要的显卡驱动之前要将nouveau先禁用掉，在终端里输入：

```bash
sudo vim /etc/modprobe.d/blacklist-nouveau.conf
```

&emsp;&emsp;sudo是行使管理员权限的前缀，会要求你输入在安装Ubuntu时给账号设定的密码，vim是一款文档编辑器，使用方法和我们在Windows下的不太一样，建议先去百度一下使用方法，这条指令是在/etc/modprobe.d目录下建立一个叫blacklist-nouveau.conf的配置文件，在vim编辑器中输入以下两行：

```bash
blacklist nouveau  
options nouveau modset=0
```

&emsp;&emsp;简单一提，输入模式按键盘上的字母i键开启，编辑结束之后，先按ESC退出编辑模式，然后输入冒号“:”,会发现在右下角出现冒号，然后在冒号之后输入wq，再回车，结束编辑，w表示保存，q表示退出。

&emsp;&emsp;然后让我们的配置文件生效，终端中输入：

```bash
sudo update-initramfs –u
```

(2) 接下来安装一些后面会用到的32位lib，终端中依次输入：

```bash
sudo apt-get install lib32ncurses5
sudo apt-get install lib32z1 
```

&emsp;&emsp;然后重启，输入：

```bash
sudo reboot
```

(3) 再次进入系统，可能会发现图像质量明显下降，不要着急，同时按下Ctrl+Alt+F1进入没有图形界面存在的荒野，然后首先登陆账号，先输入用户名，再输入密码。

&emsp;&emsp;然后关闭图形界面服务，输入：

```bash
sudo service lightdm stop
```

&emsp;&emsp;把路径导入到之前存放显卡驱动的位置，输入：

```bash
cd  /home/你的用户名/Downloads
```

&emsp;&emsp;为安装文件提高权限，输入：

```bash
sudo chmod a+x NVIDIA-Linux-x86_64-384.98.run
```

&emsp;&emsp;这里要注意文件名，后面的版本号要和实际文件对应，不要照抄照搬。

&emsp;&emsp;接下来开始安装：

```bash
sudo ./NVIDIA-Linux-x86_64-384.98.run
```

&emsp;&emsp;下面的几个选项，有一个会提示你说明文档损坏，是否继续，这里选择继续，其余的都按照默认选项即可。

&emsp;&emsp;然后重启图形界面：

```bash
sudo service lightdm start
```

&emsp;&emsp;然后同时按下Ctrl+Alt+F7切回到图形界面，图像正常，打开终端，输入：

```bash
nvidia-smi
```

&emsp;&emsp;显示如下提示信息表示安装成功。

&emsp;&emsp;接下来重启计算机，输入：

```bash
sudo reboot
```

## 3. 安装CUDA

&emsp;&emsp;电脑重新启动之后，让我们来安装CUDA，和之前类似，按下Ctrl+Alt+F1，登录，输入：

```bash
sudo service lightdm stop
cd /home/你的用户名/Downloads
sudo chmod a+x cuda_8.0.61_375.26_linux.run
sudo sh cuda_8.0.61_375.26_linux.run
```

&emsp;&emsp;仍然要注意文件的名字，保证版本号和自己下载的文件一致，不要照葫芦画瓢。虽然CUDA的文件很大，但是整个安装过程会很快，首先看完整个用户协议，输入accept，中间会问你是否安装显卡驱动，由于之前我们已经安装过了，这里选择否，其它选项如图。

![](https://pic1.zhimg.com/80/v2-cbc2a4333c9499b556a2b63f5cc74e60_hd.jpg)

&emsp;&emsp;安装完成之后我们会发现系统提示我们缺少一些依赖库，在有网络连接的情况下

![](https://pic4.zhimg.com/80/v2-cf8e2f92beefaf379a4a71a17c595d57_hd.jpg)

&emsp;&emsp;输入如下指令安装依赖库：

```bash
sudo apt-get install freeglut3-dev build-essential libx11-dev libxmu-dev libxi-dev libgl1-mesa-glx libglu1-mesa libglu1-mesa-dev
```

&emsp;&emsp;然后重启图形界面：

```bash
sudo service lightdm start
```

&emsp;&emsp;接下来测试例子：

```bash
cd  /usr/local/cuda-8.0/samples/1_Utilities/deviceQuery
sudo make
./deviceQuery
```

&emsp;&emsp;出现result：Pass则表示安装成功

&emsp;&emsp;接下来我们配置环境变量：

```bash
sudo vim /etc/profile
```

&emsp;&emsp;在结尾添加如下两行：

```bash
export  PATH=/usr/local/cuda-8.0/bin:$PATH
export  LD_LIBRARY_PATH=/usr/local/cuda-8.0/lib64:$LD_LIBRARY_PATH
```

&emsp;&emsp;然后是编辑配置文件，输入：

```bash
sudo gedit ~/.bashrc
```

&emsp;&emsp;在结尾处添加如下三行：

```bash
export PATH=/usr/local/cuda-8.0/bin${PATH:+:${PATH}}
export LD_LIBRARY_PATH=/usr/local/cuda-8.0/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
export CUDA_HOME=/usr/local/cuda-8.0
```

&emsp;&emsp;运行一下配置脚本使其生效，输入

```bash
source ~/.bashrc
```

&emsp;&emsp;然后创建一个链接文件，输入：

```bash
sudo vim /etc/ld.so.conf.d/cuda.conf
```

&emsp;&emsp;写下如下一行：

```bash
/usr/local/cuda-8.0/lib64
```

&emsp;&emsp;让链接文件生效：

```bash
sudo ldconfig
```

&emsp;&emsp;查看一下版本：

```bash
nvcc –V
```

&emsp;&emsp;别忘了接着安装之前一起下载的补丁：

```bash
cd /home/pil/Downloads
sudo sh cuda_8.0.61.2_linux.run
```

&emsp;&emsp;重启电脑：

```bash
sudo reboot
```

<br>

## 4. 安装cuDNN

&emsp;&emsp;cuDNN的文件其实就是一个压缩包，将其移动到刚刚安好的CUDA相应路径下即可，打开终端，解压文件：

```bash
cd /home/pil/Downloads
tar -zxvf cudnn-8.0-linux-x64-v7.tgz
```

&emsp;&emsp;复制文件到指定目录下并提高文件权限：

```bash
sudo cp cuda/include/cudnn.h /usr/local/cuda-8.0/include
sudo cp cuda/lib64/libcudnn* /usr/local/cuda-8.0/lib64 
sudo chmod a+r /usr/local/cuda-8.0/include/cudnn.h /usr/local/cuda-8.0/lib64/libcudnn*
```

&emsp;&emsp;将文件连接起来，输入：

```bash
cd /usr/local/cuda-8.0/lib64/  
sudo ln -sf libcudnn.so.7.0.3 libcudnn.so.7  
sudo ln -sf libcudnn.so.7 libcudnn.so  
```

&emsp;&emsp;让连接生效：

```bash
sudo ldconfig
```

<br>

## 5. 安装PyTorch

可直接参照[PyTorch官网](https://pytorch.org/get-started/locally/)：

```bash
# Python 3.5
pip3 install https://download.pytorch.org/whl/cpu/torch-1.0.1-cp35-cp35m-win_amd64.whl
pip3 install torchvision
```


<br>
<br>
<br>
<br>

## Reference:

1. [深度学习环境搭建指南Ubuntu16.04+CUDA8.0+cuDNN7.0+Anaconda+Pytorch](https://zhuanlan.zhihu.com/p/35509593)

2. [PyTorch官网](https://pytorch.org/get-started/locally/)

3. [Ubuntu16.04 安装NVIDIA英伟达驱动教程 及常见几种报错Error的解决方案](https://blog.csdn.net/ksws0292756/article/details/79160742)

4. [ubuntu 上NVIDIA驱动和CUDA9.0 的坑之一二](https://blog.csdn.net/lipi37/article/details/79465685)