# 二叉树的操作

class BinaryTreeNode:
    def __init__(self, value = None, left = None, right = None):
        self.value = value
        self.left = left
        self.right = right

class BinaryTree:
    def __init__(self):
        self.root = BinaryTreeNode

    # 在树中加入节点


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
        print(root.value)
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
