from typing import List
class Solution:
    def countPartitions(self, nums: List[int]) -> int:
        total_sum  = sum(nums)
        current_sum = 0
        count = 0
        for i in range(len(nums) - 1):
            current_sum += nums[i]
            if ((total_sum - 2 * current_sum) % 2 == 0):
                count+=1
        return count