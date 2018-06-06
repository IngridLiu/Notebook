# PyTorch定义自己的Dataset
<br>
<br>

## 1 什么是Datasets:

&emsp;&emsp;在输入流水线中，我们看到准备数据的代码是这么写的data = datasets.CIFAR10("./data/", transform=transform, train=True, download=True)。datasets.CIFAR10就是一个Datasets子类，data是这个类的一个实例。

<br>

## 2 为什么要定义Datasets:

&emsp;&emsp;PyTorch提供了一个工具函数torch.utils.data.DataLoader。通过这个类，我们在准备mini-batch的时候可以多线程并行处理，这样可以加快准备数据的速度。Datasets就是构建这个类的实例的参数之一。

<br>

## 3 如何自定义Datasets

&emsp;&emsp;下面是一个自定义Datasets的框架:
```
class CustomDataset(data.Dataset):#需要继承data.Dataset
    def __init__(self):
        # TODO
        # 1. Initialize file path or list of file names.
        pass
    def __getitem__(self, index):
        # TODO
        # 1. Read one data from file (e.g. using numpy.fromfile, PIL.Image.open).
        # 2. Preprocess the data (e.g. torchvision.Transform).
        # 3. Return a data pair (e.g. image and label).
        #这里需要注意的是，第一步：read one data，是一个data
        pass
    def __len__(self):
        # You should change 0 to the total size of your dataset.
        return 0

```
&emsp;&emsp;下面看一下官方MNIST的例子（代码被缩减，只留下了重要的部分）：
```
class MNIST(data.Dataset):
    def __init__(self, root, train=True, transform=None, target_transform=None, download=False):
        self.root = root
        self.transform = transform
        self.target_transform = target_transform
        self.train = train  # training set or test set

        if download:
            self.download()

        if not self._check_exists():
            raise RuntimeError('Dataset not found.' +
                               ' You can use download=True to download it')

        if self.train:
            self.train_data, self.train_labels = torch.load(
                os.path.join(root, self.processed_folder, self.training_file))
        else:
            self.test_data, self.test_labels = torch.load(os.path.join(root, self.processed_folder, self.test_file))

    def __getitem__(self, index):
        if self.train:
            img, target = self.train_data[index], self.train_labels[index]
        else:
            img, target = self.test_data[index], self.test_labels[index]

        # doing this so that it is consistent with all other datasets
        # to return a PIL Image
        img = Image.fromarray(img.numpy(), mode='L')

        if self.transform is not None:
            img = self.transform(img)

        if self.target_transform is not None:
            target = self.target_transform(target)

        return img, target

    def __len__(self):
        if self.train:
            return 60000
        else:
            return 10000
```

<br>
<br>
<br>
<br>
## Reference:
1. [pytorch学习笔记（六）：自定义Datasets](https://blog.csdn.net/u012436149/article/details/69061711)
