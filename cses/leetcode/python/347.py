#using bucket sort
from typing import List
from collections import Counter
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        counter = Counter(nums)
        print(counter)
        max_freq = max(counter.values())
        
        #list of empty buckets
        buckets = [[] for i in range(max_freq+1)]
        
        for num, freq in counter.items():
            buckets[freq].append(num)