"""
3550. Smallest Index With Digit Sum Equal to Index
https://leetcode.com/problems/smallest-index-with-digit-sum-equal-to-index/

You are given a 0-indexed integer array nums.

Return the smallest index i such that the sum of the digits of nums[i] is
equal to i. If no such index exists, return -1.

Example 1:
    Input:  nums = [1,3,2]
    Output: 2
    Explanation: For each index i, digitSum(nums[i]) is computed. The smallest
    index for which digitSum(nums[i]) == i is 2 because
    digitSum(nums[2]) = digitSum(2) = 2.

Example 2:
    Input:  nums = [1,10,11]
    Output: 0
    Explanation: For each index i, digitSum(nums[i]) is computed. The smallest
    index for which digitSum(nums[i]) == i is 0 because
    digitSum(nums[0]) = digitSum(1) = 1.

Example 3:
    Input:  nums = [1,2,3]
    Output: -1
    Explanation: No index matches.

Constraints:
    - 1 <= nums.length <= 100
    - 0 <= nums[i] <= 1000
"""
from typing import List
class Solution:
    @staticmethod
    def sumDigits(nums):
        ans = 0
        while nums > 0:
            ans += (nums%10)
            nums = nums//10
        return ans
    def smallestIndex(self, nums: List[int]) -> int:
        n = len(nums)
        for i in range(n):
            if i == Solution.sumDigits(nums[i]):
                return i
        return -1
