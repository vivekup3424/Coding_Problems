from typing import List
from collections import defaultdict,deque
class Solution:
    def sumOfDistancesInTree(self, n: int, edges: List[List[int]]) -> List[int]:
        #construct the graph 
        graph = defaultdict(list) 
        for edge in edges:
            u,v = edge[0], edge[1]
            graph[u].append(v)
            graph[v].append(u)
        
        #finding the number of nodes in a subtree
        numOfNodes = [1] * n
        visited = [False] * n
        def dfs(source):
            visited[source] = True
            for children in graph[source]:
                if not visited[children]:
                    numOfNodes[source] += dfs(children) #accumulate the subtree size
            return numOfNodes[source]
        root = 0
        dfs(root)
        totalNodes = numOfNodes[root]

        #finding the distances of nodes from root
        visited = [False]*n
        queue = deque()
        distanceFromRoot = 0

        queue.append((root,0)) # (a,b) a - node, b - distance from root
        visited[root] = True
        while queue:
            node, dist = queue.popleft()
            distanceFromRoot += dist
            for neighbor in graph[node]:
                if not visited[neighbor]:
                    visited[neighbor] = True
                    queue.append((neighbor,dist+1))
        print("totalNodes = ", totalNodes)
        #find the distances of each node 
        distances = [-1]*n #-1 will imply visited node
        queue = deque() #(parentNode, childNode) using parentNode find the sum of distances for child node
        queue.append((-1,root))
        while queue:
            parentNode, currentNode = queue.popleft()
            if parentNode == -1:
                distances[currentNode] = distanceFromRoot
            else:
                distances[currentNode] = distances[parentNode]  - numOfNodes[currentNode] + (totalNodes - numOfNodes[currentNode])
            for neighbor in graph[currentNode]:
                if distances[neighbor]==-1:
                    queue.append((currentNode,neighbor))
        return distances