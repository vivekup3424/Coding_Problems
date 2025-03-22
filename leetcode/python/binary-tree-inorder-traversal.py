from typing import Optional, List
class TreeNode:
    def __init__(self,val = 0, left = None, right = None) -> None:
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def inorderTraversal(self, root: Optional[TreeNode])->List[int]:
        ans = []
        def dfs(src: Optional[TreeNode]):
            if src is None:
                return
            dfs(src.left) 
            ans.append(src.val)
            dfs(src.right)
        dfs(root)
        return ans