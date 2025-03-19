from typing import List
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        ops = 0 
        for i in range(len(nums)-2):
            if(nums[i]==0):
                ops+=1
                nums[i]=1-nums[i]
                nums[i+1]=1-nums[i+1]
                nums[i+2]=1-nums[i+2]
        for i in range(len(nums)):
            if (nums[i]==0):
                return -1
        return ops