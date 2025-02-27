from typing import Optional
from collections import deque
class TreeNode:
    def __init__(self, val = 0, left = None, right = None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def recoverFromPreorder(self, traversal:str)->Optional[TreeNode]:
        stack = deque()
        i,n = 0,len(traversal)
        while i < n:
            depth = 0
            while i < n and traversal[i] == '-':
                depth+=1
                i+=1
            num = 0
            while i < n and traversal[i].isdigit:
                num = 10 * num + int(traversal[i])
                i+=1
            newNode = TreeNode(num)
            while stack and stack[-1][1] >= depth:
                stack.pop()
            if stack:
                parent, _ = stack[-1]
                if parent.left is None:
                    parent.left = newNode
                else:
                    parent.right = newNode
            stack.append((newNode,depth))
        return stack[0][0]