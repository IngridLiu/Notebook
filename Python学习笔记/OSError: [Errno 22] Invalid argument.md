# OSError: [Errno 22] Invalid argument
<br>
<br>

## 1 问题描述
&emsp;&emsp;使用pickle.dump(x, fp, protocol = 4)遇到OSError: [Errno 22] Invalid argument问题。

<br>

## 2 解决思路
&emsp;&emsp;此问题[issue24658](https://bugs.python.org/issue24658)是一个简单的输入输出问题，由文件过大引起。只需要使用pickle.loads及pickle.loads将字节对象分为几个块，每个块大小为2**31 - 1。

<br>
<br>

## 3 代码实现
&emsp;&emsp;具体实现代码如下：
```
import pickle

class MacOSFile(object):

    def __init__(self, f):
        self.f = f

    def __getattr__(self, item):
        return getattr(self.f, item)

    def read(self, n):
        # print("reading total_bytes=%s" % n, flush=True)
        if n >= (1 << 31):
            buffer = bytearray(n)
            idx = 0
            while idx < n:
                batch_size = min(n - idx, 1 << 31 - 1)
                # print("reading bytes [%s,%s)..." % (idx, idx + batch_size), end="", flush=True)
                buffer[idx:idx + batch_size] = self.f.read(batch_size)
                # print("done.", flush=True)
                idx += batch_size
            return buffer
        return self.f.read(n)

    def write(self, buffer):
        n = len(buffer)
        print("writing total_bytes=%s..." % n, flush=True)
        idx = 0
        while idx < n:
            batch_size = min(n - idx, 1 << 31 - 1)
            print("writing bytes [%s, %s)... " % (idx, idx + batch_size), end="", flush=True)
            self.f.write(buffer[idx:idx + batch_size])
            print("done.", flush=True)
            idx += batch_size


def pickle_dump(obj, file_path):
    with open(file_path, "wb") as f:
        return pickle.dump(obj, MacOSFile(f), protocol=pickle.HIGHEST_PROTOCOL)


def pickle_load(file_path):
    with open(file_path, "rb") as f:
        return pickle.load(MacOSFile(f))
```

&emsp;&emsp;用pickle_dump(obj, file_path), pickle_load(file_path)代替pickle.dump(),pickle.load()即可。