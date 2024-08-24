class Node:
    def __init__(self, val = 0, neighbors = None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []

from typing import Optional, DefaultDict, Deque
class Solution:
    def cloneGraph(self, node: Optional['Node']) -> Optional['Node']:
        if node == None:
            return None
        clonedNodes =  DefaultDict(Node)
        clonedNodes[node.val] = Node(node.val,node.neighbors)
        q = []
        while len(q) > 0:
            current = q[0]
            q = q[1:]
            for neighbor in current.neighbors:
                clonedNodes[neighbor.val] = Node(neighbor.val,neighbor.neighbors)
                q.append(neighbor)
        return clonedNodes[node.val]