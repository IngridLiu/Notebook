class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Tree:

    # 二叉树的层次遍历
    def printFromTopToBottom(self, root):

        # 利用队列，按队列访问每个节点，依次将每个节点的左孩子、右孩子入队列
        # node 记录当前访问节点
        # queue 记录当前的queue
        # result 记录返回的结果
        if not root:
            return []
        queue = []
        result = []
        queue.append(root)
        while queue:
            node = queue.pop(0)
            result.append(node.val)
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
        return result

    # 二叉搜索树的后序遍历判断
    def digui(self, num):
        if len(num) == 1 or len(num) == 0:
            return True
        b = num[-1]
        i = 0
        while num[i] < b:
            i += 1
        j = i
        while num[j] > b:
            j += 1
        if num[j] is not num[-1]:
            return False
        else:
            return self.digui(num[:i]) * self.digui(num[i:j])

    def VerifySquenceOfBST(self, sequence):
        # write code here
        if len(sequence) == 0:
            return False
        return self.digui(sequence)


if __name__ == '__main__':
    sequence = [1, 2, 3, 4, 5]
    tree = Tree()
    tree.VerifySquenceOfBST(sequence)