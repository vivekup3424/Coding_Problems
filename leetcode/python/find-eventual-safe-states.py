from typing import List
#initial assume everynode is not a safe node
class Solution:
    def eventaulSafeNodes(self,graph: List[List[int]]) -> List[int]:
        n = len(graph)
        safe = {}
        res = []
        def dfs(i):
            if i in safe:
                return safe[i]
            safe[i] = False
            for nei in graph[i]:
                if not dfs(nei):
                    return 
            safe[i] = True
            return safe[i]
        for i in range(n):
            if dfs(i):

