class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def rangeSumBST1(self, root: TreeNode, low: int, high: int) -> int:
        total_sum = 0
        def dfs(root):
            nonlocal total_sum
            if root is None:
                return 
            if root.val >= low and root.val <= high:
                total_sum += root.val
            dfs(root.left)
            dfs(root.right)
        dfs(root)
        return total_sum
    def rangeSumBST(self, root: TreeNode, low: int, high: int) -> int:
        if not root:
            return 0
        elif root.val < low:
            return self.rangeSumBST(root.right,low,high)
        elif root.val > high:
            return self.rangeSumBST(root.left, low, high)
        else:
            return root.val + self.rangeSumBST(root.left) + self.rangeSumBST(root.right)

        