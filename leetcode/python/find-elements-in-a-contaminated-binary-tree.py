from collections import deque
from typing import Optional
class TreeNode:
    def __init__(self, val = 0, left = None, right = None):
        self.val = val
        self.left = left
        self.right = right

class FindElements:
    def __init__(self, root: Optional[TreeNode]):
        if root is None:
            return;
        root.val = 0
        queue = deque()
        self.elements = set()
        queue.append(root)
        while queue:
            topNode = queue.popleft()
            self.elements.add(topNode.val)
            if topNode.left is not None:
                topNode.left.val = 2 * topNode.val + 1
                queue.append(topNode.left)    
            if topNode.right is not None:
                topNode.right.val = 2 * topNode.val + 2
                queue.append(topNode.right)
        print(self.elements) 
    
    def find(self, target : int)->bool:
        return target in self.elements()