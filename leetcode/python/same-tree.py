from typing import Optional
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def isSameTree(self,root1 : Optional[TreeNode], root2:Optional[TreeNode])->bool:
        if root1 is None and root2 is None:
            return True
        if root1 is None and root2 is not None:
            return False
        elif root2 is None and root1 is not None:
            return False
        elif root1.val != root2.val:
            return False
        return self.isSameTree(root1.left,root2.left) and self.isSameTree(root1.right,root2.right)