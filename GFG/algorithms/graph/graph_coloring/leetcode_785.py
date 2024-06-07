from collections import List
class Solution:
    def colorGraph(self, graph, src, prevColor, colors):
        newColor = abs(1 - prevColor)
        if colors[src] == prevColor:
            return False
        for child in range(graph[src]):
            if()
    def isBipartite(self, graph: List[List[int]]) -> bool:
        n = len(graph)
        colors = [-1]*n
        for i in range(colors):
            if colors[i] is -1 :


