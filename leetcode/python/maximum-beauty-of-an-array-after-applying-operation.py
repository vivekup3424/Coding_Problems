"""
You are given a 0-indexed array nums and a non-negative integer k.

In one operation, you can do the following:

    Choose an index i that hasn't been chosen before from the range [0, nums.length - 1].
    Replace nums[i] with any integer from the range [nums[i] - k, nums[i] + k].

The beauty of the array is the length of the longest subsequence consisting of equal elements.

Return the maximum possible beauty of the array nums after applying the operation any number of times.

Note that you can apply the operation to each index only once.

A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the order of the remaining elements.
"""

from typing import DefaultDict


class Solution:
    def maximumBeauty(self, nums: List[int], k: int) -> int:
        val = DefaultDict(int)
        for num in nums:
            left, right = num - k, num + k
            val[left] += 1
            val[right + 1] += -1
        print(val)


def main():
    nums = map
