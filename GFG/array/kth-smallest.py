from typing import List
import heapq
class Solution:
    def find_kth_smallest(self,arr: List[int], k:int) -> int:
        max_heap: List[int] = []
        for num in arr:
            heapq.heappush(max_heap, -num)
            if len(max_heap) > k:
                heapq.heappop(max_heap)
        return -max_heap[0]