"""
3105. Longest Strictly Increasing or Strictly Decreasing Subarray
https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/

You are given an array of integers nums. Return the length of the longest
subarray of nums which is either strictly increasing or strictly decreasing.

Example 1:
    Input:  nums = [1,4,3,3,2]
    Output: 2
    Explanation: The strictly increasing subarrays of nums are [1], [2], [3],
    [3], [4], and [1,4]. The strictly decreasing subarrays of nums are [1],
    [2], [3], [3], [4], [3,2], and [4,3]. Hence, we return 2.

Example 2:
    Input:  nums = [3,3,3,3]
    Output: 1
    Explanation: The strictly increasing subarrays of nums are [3], [3], [3],
    and [3]. The strictly decreasing subarrays of nums are [3], [3], [3], and
    [3]. Hence, we return 1.

Example 3:
    Input:  nums = [3,2,1]
    Output: 3
    Explanation: The strictly increasing subarrays of nums are [3], [2], and
    [1]. The strictly decreasing subarrays of nums are [3], [2], [1], [3,2],
    [2,1], and [3,2,1]. Hence, we return 3.

Constraints:
    - 1 <= nums.length <= 50
    - 1 <= nums[i] <= 50
"""
from typing import List
class Solution:
    def longestMonotonicSubarray(self, nums: List[int]) -> int:
        max_length = 1
        prev_diff = 0
        length = 1
        for i in range(1,len(nums)):
            diff = nums[i]-nums[i-1]
            if diff == 0:
                length = 1
            elif prev_diff * diff > 0:
                length+=1
            else:
                length = 2
            prev_diff = diff
            max_length = max(max_length,length)
        return max_length

