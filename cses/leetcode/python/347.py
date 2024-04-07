#using bucket sort
from collections import Counter
from typing import List


class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        frequencyHashmap = {}
        for num in nums:
            if num in frequencyHashmap:
                frequencyHashmap[num]+=1
            else:
                frequencyHashmap[num] = 1
        minHeap =``
