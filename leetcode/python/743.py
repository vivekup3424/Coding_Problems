from typing import List
import collections
import math
class Solution:
    def networkDelayTime(self, times: List[List[int]], n: int, k: int) -> int:
        graph = {}
        for time in times:
            f,t,w = time
            if f in graph:
                graph[f].append((t,w))
            else:
                graph[f] = [(t,w)]
        
        visited = {}
        distance = [math.inf for]