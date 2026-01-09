from typing import Optional
from collections import deque
class TreeNode:
    def __init__(self, val : int = 0, left: Optional['TreeNode'] = None, right: Optional['TreeNode'] = None) -> None:
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def maxLevelSum(self, root: Optional[TreeNode]) -> int:
        if root is None:
            return 0
        answer = 0
        level = 0
        q = deque
        q.append()
        while q:


        return answer