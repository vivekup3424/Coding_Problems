from typing import List
class Solution:
    def countSubarrays(self, nums: List[int], k: int) -> int:        
        n = len(nums)
        pref = [0 for i in range(n)]
        for i in range(n):
            if i == 0:
                pref[i] = nums[i]
            else:
                pref[i] = nums[i] & pref[i-1]