from typing import List
from functools import cache

class Solution:
    def maxDotProduct(self, nums1: List[int], nums2: List[int]) -> int:
        @cache
        def recurse(firstIndex: int, secondIdx: int) -> int:
            """finds the maxDotProduct of subsequences ending at:
            1. index of firstIndex for nums1
            2. index of secondIndex for nums2"""
            if firstIndex < 0 or secondIdx < 0:
                return -10000
            return max((nums1[firstIndex]*nums2[secondIdx] + recurse(firstIndex-1,secondIdx-1),
                        nums1[firstIndex]*nums2[secondIdx],
                        recurse(firstIndex-1,secondIdx),
                        recurse(firstIndex,secondIdx-1)))
        return recurse(len(nums1)-1, len(nums2)-1)