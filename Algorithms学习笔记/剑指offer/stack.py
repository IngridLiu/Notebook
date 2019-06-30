

class Stack:

    def isPopOrder(self, pushV, popV):
        '''
            解题思路：
                根据pushV出栈的思路，将pushV和popV进行比较
        '''
        #stack中存入从push中取出的数
        stack = []
        while popV:
            # 如果第一个元素相等，直接都弹出，根本不用压入stack
            if pushV and popV[0] == pushV[0]:
                pushV.pop(0)
                popV.pop(0)
            elif stack and stack[-1] == popV[0]:
                stack.pop()
                popV.pop(0)
            elif pushV:
                stack.append(pushV.pop(0))
            else:
                return False
        return True

if __name__ == '__main__':
    print()