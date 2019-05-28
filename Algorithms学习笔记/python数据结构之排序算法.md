# python数据结构之排序算法

<br>
<br>

排序算法总结

|排序算法类别|排序发方法|最好情况|最坏情况|平均时间|辅助空间|稳定性|备注|
|:---------:|:--------:|:-----:|:------:|:------:|:------:|:----:|:---:|
|插入排序|直接插入排序|O(n)|O(n^2)|O(n^2)|O(1)|稳定||
||折半插入排序|O(nlogn)|O(nlogn)|O(nlogn)|O(1)|稳定||
||希尔排序|O(n(nlogn)^2)|O(n(logn)^2)|O(n(logn)^2)|O(1)|不稳定||
|交换排序|冒泡排序|O(n)|O(n^2)|O(n^2)|O(1)|稳定||
||快速排序|O(nlogn)|O(nlogn)|O(n^2)|O(logn)|不稳定||
|选择排序|直接选择排序|O(n^2)|O(n^2)|O(n^2)|O(1)|不稳定||
||堆排序|O(nlogn)|O(nlogn)|O(nlogn)|O(1)|不稳定||
||树形选择排序|O(nlogn)|O(nlogn)|O(nlogn)|O(n)|不稳定||
|归并排序|二路归并排序|O(nlogn)|O(nlogn)|O(nlogn)|O(n)|稳定||
|分配排序|桶排序|||||||
||基数排序|O(2mn)|O(2mn)|O(2mn)|O(dn)|稳定||

<br>
<br>

## 1. 插入排序

### 1.1 直接插入排序

```python
class Sort:

    # 插入排序
    # 直接插入排序
    def directInsertSort(self, s:int):
        for i in range(1, len(s)):
            key = s[i]
            j = i-1
            while s[j] > key and j >= 0:
                s[j+1] = s[j]
                s[j] = key
                j -= 1
        return s
    # 折半插入排序
    def binaryInsertSort(self, s:int):
        for i in range(1, len(s)):
            key = s[i]
            low = 0
            high = i - 1
            while low <= high:
                mid = (low + high) // 2
                if key < s[mid] :
                    high = mid - 1
                else:
                    low = mid + 1
            j = i - 1
            while j > high:
                s[j + 1] = s[j]
                s[j] = key
                j -= 1
        return s
    # 希尔排序：
    def shellSort(self, d: list, s: list):
        for span in d:
            for k in range(span):
                for i in range(k, len(s), span):
                    key = s[i]
                    j = i - span
                    while j > -1 and key < s[j]:
                        s[j+span] = s[j]
                        s[j] = key
                        j -= span
        return s
```

## 2. 交换排序

### 2.1 冒泡排序

### 2.2 快速排序

```python
    # 交换排序
    # 冒泡排序
    def bubbleSort(self, s:list):
        j = len(s) - 1
        while j > 0:
            max_key = s[0]
            for i in range(0, j):
                if s[i] > s[i + 1]:
                    temp = s[i]
                    s[i] = s[i+1]
                    s[i+1] = temp
            j -= 1
        return s
    # 快速排序
    def quickSort(self, s:list, start, end):
        if start < end:
            low = start
            high = end
            key = s[low]
            while low < high:
                # 将小于key的值往前放
                while low < high and s[high] >= key:
                    high -= 1
                s[low] = s[high]
                # 将大于key的值往后放
                while low < high and s[low] <= key:
                    low += 1
                s[high] = s[low]
            s[low] = key

            # 递归前后半区
            self.quickSort(s, start, low-1)
            self.quickSort(s, high+1, end)
        return s
```

### 3. 选择排序

### 3.1 简单选择排序

### 3.2 堆排序

### 3.3 树形选择排序

```python
    # 选择排序
    # 直接选择排序
    def directSelectSort(self, s: list):
        for i in range(len(s)):
            min_index = i
            for j in range(i, len(s)):
                if s[min_index] > s[j]:
                    min_index = j
            temp = s[min_index]
            s[min_index] = s[i]
            s[i] = temp
        return s
    # 堆排序
    
    # 树形选择排序
    
```

### 4. 归并排序

```python

    # 归并排序
    # 二路归并排序
    def merge(self, list_1: list, list_2: list):
        i = 0
        j = 0
        new_list = []
        while i < len(list_1) and j < len(list_2):
            if list_1[i] < list_2[j]:
                new_list.append(list_1[i])
                i = i + 1
            else:
                new_list.append(list_2[j])
                j = j + 1
        if i == len(list_1):
            for item in list_2[j:]:
                new_list.append(item)
        else:
            for item in list_1[i:]:
                new_list.append(item)
        return new_list
    def mergeSort(self, lists: list):
        if len(lists) <= 1:
            return lists
        middle = len(lists) // 2
        left = self.mergeSort(lists[:middle])
        right = self.mergeSort(lists[middle:])
        return self.merge(left, right)
        
```

## 5. 分配排序

### 5.1 桶排序

### 5.2 基数排序

```python
if __name__ == "__main__":
    s = [3, 6, 2 ,3, 4, 9, 8]
    sort = Sort()
    sored_s = sort.mergeSort(s)
    print(sored_s)
```