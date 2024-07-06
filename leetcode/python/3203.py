from collections import defaultdict
from typing import List
class Solution:
    def minimumDiameterAfterMerge(self, edges1: List[List[int]], edges2: List[List[int]]) -> int:
       def getDiameter(edges):
        graph = defaultdict(list)
        for i,j in edges:
            graph[i].append(j)
            graph[j].append(i)
        res = [0]
        def dfs(node,parent):
           maxDepth = 1
           for neighbor in map[node]:
              if neighbor == parent:
                 continue
              depth = dfs(node,neighbor)
              res[0] = max(res[0], maxDepth+depth)
