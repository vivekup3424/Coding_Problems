from typing import *
class TreeNode:
    def __init__(self, val = 0, left = None, right = None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def isPalindrome(self,arr: List[int])->bool:
        left, right = 0,len(arr)-1
        while left < right:
            if arr[left] != arr[right]:
                return False
            left+=1
            right-=1
        return True
    def isSymmetric(self, root: Optional[TreeNode])->bool:
        if root is None:
            return True
        queue = Deque()
        hashMap = DefaultDict(List[int])
        queue.append((root,0))
        while queue:
            node, level = queue.popleft()
            hashMap[level].append(node.val)
            if node.left is not None:
                queue.append((node.left,level+1))
            if node.right is not None:
                queue.append((node.right,level+1))
        for arr in hashMap.values():
            if self.isPalindrome(arr) is False:
                return False
        return True

