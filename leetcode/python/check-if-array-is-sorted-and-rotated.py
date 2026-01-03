from typing import List
class Solution:
    def check(self, nums: List[int]) -> bool:
        num_pivot = 0
        for i in range(len(nums)):
            if(i+1<len(nums) and nums[i] > nums[i+1]):
                num_pivot+=1
        if nums[-1] > nums[0]:
            num_pivot+=1
        return num_pivot <= 1
