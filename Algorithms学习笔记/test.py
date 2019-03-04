class Node:
    def __init__(self, value = None, next = None):
        self._value = value
        self._next = next

    def getValue(self):
        return self._value

    def getNext(self):
        return self._next

    def setValue(self, new_value):
        self._value = new_value

    def setNext(self, new_next):
        self._next = new_next


class ListNode:
   def __init__(self, x):
       self._head = Node()
       self._tail = Node()
       self._length = 0

    # 判断NodeList是否为空
   def isEmpty(self):
       return self._head == None

   # 在NodeList前添加元素
   def add(self, value):
       newnode = Node(value, None)
       newnode.setNext(self._head)
       self._head = newnode

   # 在NodeList末尾添加元素
   def append(self, value):
       newnode = Node(value, None)
       if self._head == None:
           self._head = newnode
       else:
           curr = self._head
           while curr.getNext() != None:
               curr = curr.getNext()
           curr.setNext(newnode)

   # 再NodeList中删除第一个元素
   def delete(self):
       count = 0
       curr = self._head
       self._head = curr.getNext()




    # search 元素是否在链表中
   def search(self, value):
       find_value = False
       curr = self._head
       while curr != None and not find_value:
           if curr.getValue() == find_value:
               find_value == True
           else:
               curr = curr.getNext()
       return find_value

   # index索引元素在链表中的位置：
   def index(self, value):
       position = 0
       curr = self._head
       find = False
       if curr != None and not find:
           position += 1
           if curr.getValue() == value:
               find = True
           else:
               curr.getNext()
       if find:
            return position
       else:
            raise ValueError("%s is not in linkedlist" %value)

   # index删除链表中的某个元素
   def remove(self, value):
       pre = None
       curr = self._head
       while curr != None:
           if curr.getValue() == value:
               if not pre :
                   self._head = curr.getNext()
               else:
                   pre = curr
                   pre.setNext(curr.getNext())

    # insert链表中插入元素
   def insert(self, pos, value):
       if pos <= 1:
           self.add(value)
       elif pos > self.size():
           self.append(value)
       else:
           temp = Node(value)
           count = 1
           pre = None
           current = self._head
           while count < pos:
               count += 1
               pre = current
               current = current.getNext()
           pre.setNext(temp)
           temp.setNext(current)






class Solution:
    def addTwoNumbers(self, l1:ListNode, l2:ListNode) -> ListNode:
        re = ListNode(0)
        curr = re
        carry = 0
        p = l1
        q = l2
        while (p or q):
            x = p.val if p else 0
            y = q.val if q else 0
            s = carry + x + y
            carry = s//10
            curr.next = ListNode(s % 10)
            curr = curr.next
            p = p.next if p else None
            q = q.next if q else None
        if carry > 0:
            re.next = ListNode(carry)
        return re

