"""
238. Product of Array Except Self
https://leetcode.com/problems/product-of-array-except-self/

Given an integer array nums, return an array answer such that answer[i] is
equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a
32-bit integer.

You must write an algorithm that runs in O(n) time and without using the
division operation.

Example 1:
    Input:  nums = [1,2,3,4]
    Output: [24,12,8,6]

Example 2:
    Input:  nums = [-1,1,0,-3,3]
    Output: [0,0,9,0,0]

Constraints:
    - 2 <= nums.length <= 10^5
    - -30 <= nums[i] <= 30
    - The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
"""
from typing import List
class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        n = len(nums)
        leftProductPrefix = []
        rightProductPrefix = []
        for i in range(n):
            if(i == 0):
                leftProductPrefix[i] = 1
            else:
                leftProductPrefix[i] = leftProductPrefix[i-1] * nums[i-1]
        for i in range(n-1,-1,-1):
            if(i==n-1):
                rightProductPrefix[i] = 1
            else:
                rightProductPrefix[i] = rightProductPrefix[i+1]*nums[i+1]
        ans = []
        for i in range(n):
            ans[i] = leftProductPrefix[i]*rightProductPrefix[i]
        return ans
