"""
3876. Construct Uniform Parity Array II
https://leetcode.com/problems/construct-uniform-parity-array-ii/

You are given an array nums1 of n distinct integers. You want to construct
another array nums2 of length n such that the elements in nums2 are either
all odd or all even.

For each index i, you must choose exactly one of the following (in any
order): nums2[i] = nums1[i] or nums2[i] = nums1[i] - nums1[j], for an index
j != i, such that nums1[i] - nums1[j] >= 1.

Return true if it is possible to construct such an array, otherwise return
false.

Example 1:
    Input:  nums1 = [1,4,7]
    Output: true
    Explanation: Set nums2[0] = nums1[0] = 1. Set nums2[1] = nums1[1] -
        nums1[0] = 4 - 1 = 3. Set nums2[2] = nums1[2] = 7. nums2 = [1, 3, 7],
        and all elements are odd. Thus, the answer is true.

Example 2:
    Input:  nums1 = [2,3]
    Output: false
    Explanation: It is not possible to construct nums2 such that all
        elements have the same parity.

Example 3:
    Input:  nums1 = [4,6]
    Output: true
    Explanation: nums2 = [4, 6], and all elements are already even.

Constraints:
    - 1 <= n == nums1.length <= 10^5
    - 1 <= nums1[i] <= 10^9
    - All elements in nums1 are distinct
"""
from typing import List
class Solution:
    def uniformArray(self, nums1: List[int]) -> bool:
        min_odd = -1e9
        num_odd = 0
        num_even = 0
        for n in nums1:
            if n % 2 == 1:
                min_odd = min(n,min_odd)
                num_odd += 1
            else:
                num_even += 1

