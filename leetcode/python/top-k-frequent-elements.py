from typing import List
from collections import defaultdict
import heapq
class Solution:
    def topKFrequent(self, nums: List[int], k : int) -> List[int]:
        freq_map: defaultdict[int,int] = defaultdict(int)
        for num in nums:
            freq_map[num]+=1
        