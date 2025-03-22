from typing import *
class TreeNode:
    def __int__(self, val = 0, left = None, right = None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def maxDepth(self,root: Optional[TreeNode])->int: