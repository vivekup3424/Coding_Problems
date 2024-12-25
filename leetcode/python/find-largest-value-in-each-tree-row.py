from collections import defaultdict, deque
from typing import Optional, List
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def largestValues(self, root: Optional[TreeNode]) -> List[int]:
        nodeLevels = defaultdict(list)
        answer = []
        if root is None:
            return answer
        queue = deque()
        level = 0
        queue.append((root,level))
        while queue:
            node,level = queue.popleft()
            nodeLevels[level].append(node.val)
            if node.left is not None:
                queue.append((node.left,level+1))
            if node.right is not None:
                queue.append((node.right,level+1))
        for level  in sorted(nodeLevels.keys()):
            answer.append(max(nodeLevels[level]))
        return answer

        