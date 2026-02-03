from typing import List
class Solution:
    def isTrionic(self, nums: List[int]) -> bool:
        peak_index, valley_index = -1,-1
        for i in range(1,len(nums)-1):
            if nums[i] > nums[i-1] and nums[i] > nums[i+1]:
                peak_index = i
                break

        for j in range(len(nums)-2,0,-1):
            if nums[j] < nums[j-1] and nums[j] < nums[j+1]:
                valley_index = j
                break
        
        if peak_index != -1 and valley_index != -1 and peak_index < valley_index:
            return True
        return False
