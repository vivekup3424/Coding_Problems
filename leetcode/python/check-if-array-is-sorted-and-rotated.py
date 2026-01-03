from typing import List
class Solution:
    def isSorted(self,left: int, right: int, nums: List[int]) -> bool:
        for i in range(left+1,right):
            if(nums[i]<nums[i-1]):
                return False
        return True
    def check(self,nums: List[int]) -> bool:
        peak_index = -1
        for i in range(len(nums)):
            isLeftSidePeaking = True
            if(i-1>=0 and nums[i] < nums[i-1]):
                isLeftSidePeaking = False
            isRightSidePeaking = True
            if(i+1<len(nums) and nums[i] < nums[i+1]):
                isRightSidePeaking = False
            if(isLeftSidePeaking and isRightSidePeaking):
                peak_index = i

            if(self.isSorted(0,peak_index,nums) and self.isSorted(peak_index,len(nums),nums)):
                return True
        return False