from typing import List
class Solution:
    def longestSubarray(self,nums: List[int], k : int) -> int:
        left = 0
        current_sum = 0
        maxLength = 0
        n = len(nums)
        for right in range(n):
            current_sum += nums[right]
            while current_sum > k and left <= right:
                current_sum -= nums[left]
                left -= 1
            if current_sum == k:
                maxLength = max(maxLength,right-left+1)
        return maxLength