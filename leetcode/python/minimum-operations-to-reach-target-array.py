from collections import defaultdict
from typing import List

class Solution:
    def minOperations(self, nums: List[int], target: List[int]) -> int:
        difference_map:defaultdict[int,int]= defaultdict(int)
        for i in range(len(nums)):
            if nums[i] != target[i]:
                difference_map[nums[i]]+=1
        return len(difference_map)