class Solution:
    def longestOnes(self, nums: List[int], k: int) -> int:
        max_zeroes = k
        l,r,n = 0,0,len(nums)
        maxLen = 0
        while r < n:
            while max_zeroes < 0:
                max_zeroes += (nums[l]==0)
                l+=1
            
            max_zeroes -= (nums[r]==0)
            r+=1
            maxLen = max(maxLen,r-l+1)
        