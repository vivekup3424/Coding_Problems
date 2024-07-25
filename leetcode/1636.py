from typing import List
import heapq
from collections import Counter

class Solution:
    def frequencySort(self, nums: List[int]) -> List[int]:
        # Count the frequency of each number
        frequency = Counter(nums)
        
        # Create a max-heap based on frequency
        maxHeap = [(freq, num) for num, freq in frequency.items()]
        heapq.heapify(maxHeap)
        
        # Extract elements from the heap and construct the result list
        ans = []
        while maxHeap:
            freq, num = heapq.heappop(maxHeap)
            ans.extend([num] * -freq)
        
        return ans
