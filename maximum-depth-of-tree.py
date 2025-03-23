from typing import *
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        self.max_length = 0
        def dfs(root:TreeNode,current_length:int):
            if root is None:
                return
            if root.left is None and root.right is None:
                self.max_length = max(self.max_length,current_length)
                return
            dfs(root.left,current_length+1)
            dfs(root.right,current_length+1)
        dfs(root,1)
        return self.max_length