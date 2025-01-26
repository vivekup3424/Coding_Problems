# import heapq #auto heapq is a minHeap so my work is saved, i dont need to use a minHeap
#since BFS already works in a greedy, and finds the shortest to each node from the source
#when the edge weight is constant
from collections import deque
from typing import List
class Solution:
    def highestPeak(self, isWater: List[List[int]]):
        rows,cols = len(isWater), len(isWater[0])
        minHeap = deque()
        visited = set()
        for i in range(rows):
            for j in range(cols):
                if isWater[i][j] == 1:
                    minHeap.append((i,j,0))
                    visited.add((i,j))
        directions = [(1,0),(-1,0),(0,1),(0,-1)]
        maxHeight = 0
        while len(minHeap) > 0:
            x,y,height = minHeap.popleft()
            for 
