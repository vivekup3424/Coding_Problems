from collections import defaultdict
class Solution:
    def minimumTime(self, n: int, relations: List[List[int]], time: List[int]) -> int:
        adj = defaultdict(list)
        for src, dest in relations:
            adj[src].append(dest)

        max_time = {} #dp
        def dfs