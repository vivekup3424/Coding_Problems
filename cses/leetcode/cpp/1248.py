class Solution:
    def numberOfSubarrays(self, nums: List[int], k: int) -> int:
        l = 0
        maxCount = 0 #count of the majority element
        maxLen = 0
        sum = 0
        for r,num in enumerate(nums):
            sum = 