from typing import List
from collections import defaultdict, deque
class Solution:
    def checkIfPrerequisite(self, numCourses: int, prerequisites: List[List[int]], queries: List[List[int]]) -> List[bool]:
        indegree = [0 for _ in range(numCourses)]
        adjGraph = defaultdict(set)
        for edge in prerequisites:
            u,v = edge[0], edge[1]
            indegree[v]+=1
            adjGraph[u].add(v)
        nodePrerequisites = defaultdict(set)
        q = deque()
        for i in range(numCourses):
            if indegree[i] == 0:
                q.append(i)
        while q:
            node = q.popleft()
            for adj in adjGraph[node]:
                nodePrerequisites[adj].add(node)
                for prereq in nodePrerequisites[node]:
                    nodePrerequisites[adj].add(prereq)
                indegree[adj]-=1
                if indegree[adj]==0:
                    q.append(adj)
        answer = []
        for query in queries:
            answer.append(query[0] in nodePrerequisites[query[1]])
        return answer