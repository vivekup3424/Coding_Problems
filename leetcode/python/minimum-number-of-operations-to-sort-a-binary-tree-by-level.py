from typing import Optional
from collections import deque, defaultdict
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def minimumOperations(self, root: Optional[TreeNode]) -> int:
        if root is None:
            return 0
        queue = deque()
        levelNodes = defaultdict(list)
        queue.append((root, 0))
        while queue:
            node, level = queue.popleft()
            levelNodes[level].append(node.val)
            if node.left:
                queue.append((node.left, level + 1))
            if node.right:
                queue.append((node.right, level + 1))
        count = 0
        for nodes in levelNodes.values():
            index_map = {val: idx for idx, val in enumerate(nodes)}
            sorted_nodes = sorted(nodes)
            for i in range(len(nodes)):
                while nodes[i] != sorted_nodes[i]:
                    correct_val = sorted_nodes[i]
                    to_swap_idx = index_map[correct_val]
                    index_map[nodes[i]] = to_swap_idx
                    index_map[correct_val] = i
                    nodes[i], nodes[to_swap_idx] = nodes[to_swap_idx], nodes[i]
                    count += 1
        return count
