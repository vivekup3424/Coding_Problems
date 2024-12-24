from typing import List
from collections import defaultdict, deque
class Solution:
    def minimumDiameterAfterMerge(self, edges1: List[List[int]], edges2: List[List[int]]) -> int:
        #using topological sort find the two centers of each tree
        def topoSort(edges):
            indegree = defaultdict()
            graph = defaultdict(list)
            topo = []
            queue = deque()
            for edge in edges:
                indegree[edge[0]]+=1
                indegree[edge[1]]+=1
                graph[edge[0]].append(edge[1])
                graph[edge[1]].append(edge[0])
            for key, val in indegree.items():
                if val == 1:
                    queue.append(val)
            while queue:
                node = queue.popleft()
                indegree[node]-=1
                for neighbor in graph[node]:
                    if indegree[neighbor] == 1:
                        queue.append(neighbor)
            return topo
        def dfs(gra,souce):

        topo1 = topoSort(edges1)
        topo2 = topoSort(edges2)
        centersOne = [topo1[0]]
        centersTwo = [topo2[0]]
        if len(topo1) >= 2:
            centersOne.append(topo1[1])
        if len(topo2) >= 2:
            centersTwo.append(topo2[1])
        