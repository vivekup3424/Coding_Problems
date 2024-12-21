from collections import defaultdict, deque
class Solution:
    def topologicalSort(self, adj):
        indegree = {i: 0 for i in range(len(adj))}
        for node, neighbors in adj.items():
            for neighbor in neighbors:
                indegree[neighbor] += 1
        queue = deque()
        for node, degree in indegree.items():
            if degree == 0:
                queue.append(node)
        topo_order = []
        while queue:
            node = queue.popleft()
            topo_order.append(node)
            for neighbor in adj[node]:
                indegree[neighbor] -= 1
                if indegree[neighbor] == 0:
                    queue.append(neighbor)
        return topo_order
