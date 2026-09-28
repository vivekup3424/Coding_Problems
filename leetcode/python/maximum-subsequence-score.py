"""
2542. Maximum Subsequence Score
https://leetcode.com/problems/maximum-subsequence-score/

You are given two 0-indexed integer arrays nums1 and nums2 of equal length n
and a positive integer k. You must choose a subsequence of indices from
nums1 of length k.

For chosen indices i0, i1, ..., ik - 1, your score is defined as:
    sum of nums1[i0], nums1[i1], ..., nums1[ik - 1] multiplied by the minimum
    of nums2[i0], nums2[i1], ..., nums2[ik - 1].

It can also be defined as sum(nums1[i0], nums1[i1], ..., nums1[ik - 1]) * min(nums2[i0], nums2[i1], ..., nums2[ik - 1]).

Return the maximum possible score.

A subsequence of indices of an array is a set that can be derived from the
array by deleting some or no elements without changing the order of the
remaining elements.

Example 1:
    Input:  nums1 = [1,3,3,2], nums2 = [2,1,3,4], k = 3
    Output: 12
    Explanation: The four possible subsequence scores are:
        - We choose the indices 0, 1, and 2, with score = (1+3+3) * min(2,1,3) = 7.
        - We choose the indices 0, 1, and 3, with score = (1+3+2) * min(2,1,4) = 6.
        - We choose the indices 0, 2, and 3, with score = (1+3+2) * min(2,3,4) = 12.
        - We choose the indices 1, 2, and 3, with score = (3+3+2) * min(1,3,4) = 8.
        So we return the max score, which is 12.

Example 2:
    Input:  nums1 = [4,2,3,1,1], nums2 = [7,5,10,9,6], k = 1
    Output: 30
    Explanation: Choosing index 2 is optimal: nums1[2] * nums2[2] = 3 * 10 = 30 is the maximum possible score.

Constraints:
    - n == nums1.length == nums2.length
    - 1 <= n <= 10^5
    - 0 <= nums1[i], nums2[j] <= 10^5
    - 1 <= k <= n
"""
from typing import List
import heapq

class Solution:
    def maxScore(self, nums1: List[int], nums2: List[int], k: int) -> int:
        nums = [(n1,n2) for n1, n2 in zip(nums1,nums2)]
        nums = sorted(nums, key=lambda p : p[1], reverse=True)
        minheap = []
        res, n1_sum = -float("inf"), 0
        for n1, n2 in nums:
            n1_sum+=n1
            heapq.heappush(minheap)
            if len(minheap) > k:
                n1_pop = heapq.heappop(minheap)
                n1_sum -= n1_pop
            if len(minheap) == k:
                res = max(res, n1_sum * n2)
        return res
