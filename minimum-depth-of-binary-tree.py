from typing import *
class TreeNode:
    def __init__(self,_val=0,_left=None,_right=None):
        self.val = _val
        self.left = _left
        self.right = _right
class Solution:
    def minDepth(self, root:Optional[TreeNode])->int:
        self.minValue = 1000001
        def dfs(node: Optional[TreeNode], depth: int):
            if node.left is None and node.right is None:
                self.minValue = min(self.minValue,depth)
            dfs(node.left, depth+1)
            dfs(node.right, depth+1)
        dfs(root,0)
        return self.minValue