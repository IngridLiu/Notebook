# python数据结构之树与二叉树

<br>
<br>

## 1. 树

## 2. 二叉树的定义与性质

### 2.1 二叉树的定义和性质

满二叉树：二叉树中所有分支节点的度数都为2，且叶子节点都在同一层上。

完全二叉树：相当于满二叉树从右向左删掉若干个叶子节点；

二叉排序树：（1）若左子树不空，则左子树上所有节点的值均小于它的根节点的值；（2）若右子树不空，则右子树上所有节点的值均大于它的根节点的值；（3）左、右子树也分别为二叉排序树；（4）没有键值相等的节点；


### 2.2 二叉树的存储结构

### 2.3 二叉树链式存储结构下的操作

```python
# 二叉树的操作

class BinaryTreeNode:
    def __init__(self, value = None, left = None, right = None):
        self.value = value
        self.left = left
        self.right = right

class BinaryTree:
    def __init__(self):
        self.root = BinaryTreeNode

    # 二叉树的递归遍历
    # 递归前序遍历
    def preOrderRecursive(self, root):
        '''
        优先访问根节点，再分别访问左子树和右子树。
        :param root:
        :return:
        '''
        if root == None:
            return
        print(root.value)
        self.preOrderRecursive(root.left)
        self.preOrderRecursive(root.right)
    # 递归中序遍历
    def inOrderRecursive(self, root):
        if root == None:
            return
        self.inOrderRecursive(root.left)
        print(root.value)
        self.inOrderRecursive(root.right)
    # 递归后序遍历
    def afterOrderRecursive(self, root):
        if root == None:
            return
        self.afterOrderRecursive(self, root.left)
        self.afterOrderRecursive(self, root.right)
        print(root.value)


    # 堆栈实现二叉树遍历（非递归）
    # 前序遍历
    def preOrderStack(self, root):
        if root == None:
            return
        stack = []
        binaryTreeNode = root
        while stack or binaryTreeNode:
            while binaryTreeNode:
                print(binaryTreeNode.value)
                stack.append(binaryTreeNode)
                binaryTreeNode = binaryTreeNode.left
            binaryTreeNode = stack.pop()
            binaryTreeNode = binaryTreeNode.right

    # 中序遍历
    def inOrderStack(self, root):
        if root == None:
            return
        stack = []
        binaryTreeNode = root
        while stack or binaryTreeNode:
            while binaryTreeNode:
                stack.append(binaryTreeNode)
                binaryTreeNode = binaryTreeNode.left
            binaryTreeNode = stack.pop()
            print(binaryTreeNode.value)
            binaryTreeNode = binaryTreeNode.right

    # 后序遍历
    def afterOrderStack(self, root):
        if root == None:
            return
        stack_1 = []
        stack_2 = []
        binaryTreeNode = root
        while stack_1 or binaryTreeNode:
            while binaryTreeNode:
                stack_2.append(binaryTreeNode)
                stack_1.append(binaryTreeNode)
                binaryTreeNode = binaryTreeNode.right
            binaryTreeNode = stack_1.pop()
            binaryTreeNode = binaryTreeNode.left
        while stack_2:
            print(stack_2.pop().value)

    # 实现层次遍历
    def levelOrderQueue(self, root):
        if root == None:
            return
        queue = []
        binaryTreeNode = root
        queue.append(binaryTreeNode)
        while queue:
            binaryTreeNode = queue.pop(0)
            print(binaryTreeNode.value)
            if binaryTreeNode.left:
                queue.append(binaryTreeNode.left)
            if binaryTreeNode.right:
                queue.append(binaryTreeNode.right)


if __name__ == '__main__':
    root = BinaryTreeNode('D', left=BinaryTreeNode('B', left=BinaryTreeNode('A'), right=BinaryTreeNode('C')), right=BinaryTreeNode('E', right=BinaryTreeNode('G', left=BinaryTreeNode('F'))))
    binaryTree = BinaryTreeNode()
    print('前序遍历')
    binaryTree.preOrderRecursive(root)


```

## 7. 树的应用

### 7.1 分类二叉树（二叉排序树、二叉搜索树）

分类二叉树又称为二叉排序树、二叉搜索树，定义为：（1）若左子树不空，则左子树上所有节点的值均小于它的根节点的值；（2）若右子树不空，则右子树上所有节点的值均大于它的根节点的值；（3）左、右子树也分别为二叉排序树；（4）没有键值相等的节点；

如果按中序遍历遍历一颗二叉排序树，其结果是一个按某一特征值（关键字）升序排序的线性序列；

分类二叉树实现：

```python
# 分类二叉树中数据元素的查找


# 将节点插入到分类二叉树中


# 删除分类二叉树中的节点


```

### 7.2 堆树

最大树：每个节点的值都大于或等于其孩子节点的（如果存在）的值的一般树（或二叉树）。

最小树：每个节点的值都小于或等于其孩子节点的（如果存在）的值的一般树（或二叉树）。

最大（小）堆：堆树是一颗完全二叉树；如果一棵完全二叉树本身满足最大树的条件，则这棵完全二叉树就是最大堆；如果一棵完全二叉树本身满足最小树的条件，则这棵完全二叉树就是最小堆。


