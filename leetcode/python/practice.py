from typing import List
import heapq
class MaxHeap:
    def __init__(self):
        self.heap = []
    
    def push(self, val, x, y):
        # Use negative value to simulate max heap
        heapq.heappush(self.heap, (-val, x, y))
    
    def pop(self):
        # Pop the element with the maximum value
        neg_val, x, y = heapq.heappop(self.heap)
        return (-neg_val, x, y)
    
    def peek(self):
        # Peek at the element with the maximum value without popping it
        if not self.heap:
            return None
        neg_val, x, y = self.heap[0]
        return (-neg_val, x, y)
    
    def __len__(self):
        return len(self.heap)
class Solution:
    def maximumScore(self, grid: List[List[int]]) -> int:
        max_heap = MaxHeap()
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                max_heap.push(grid[i][j], i, j)
        
        count = 0
        while max_heap:
            count += 1
            val, x, y = max_heap.pop()
            if val == 0:
                grid[x][y] = -1
            else:
                count += val
                for i in range(0,x):
                    grid[i][y] = -1