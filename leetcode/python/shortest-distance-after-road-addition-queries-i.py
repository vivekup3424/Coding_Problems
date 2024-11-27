from collections import defaultdict
import heapq
from typing import List
from math import inf


class Solution:
    def shortestDistanceAfterQueries(
        self, n: int, queries: List[List[int]]
    ) -> List[int]:
        graph = defaultdict(list)
        for i in range(0, n):
            print(f"{i}->{i+1}")
            graph[i].append(i + 1)
        distance = [inf] * n
        distance[0] = 0
        priority_queue = [(0, 0)]
        while priority_queue:
            dist, node = heapq.heappop(priority_queue)
        return distance
