from typing import List
from collections import defaultdict
class Solution:
    def minimumOperations(self, nums: List[int]) -> int:
        n = len(nums)
        freq = defaultdict()
        for i in range(n-1,-1,-1):
            freq[nums[i]]+=1
            if((n-i)!=len(freq)){
                freq[nums[i]]-=1
                break
            }