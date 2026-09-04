"""
3903. Smallest Stable Index I
https://leetcode.com/problems/smallest-stable-index-i/

You are given an integer array nums of length n and an integer k. For each
index i, define its instability score as max(nums[0..i]) - min(nums[i..n-1]),
where max(nums[0..i]) is the largest value among the elements from index 0 to
index i, and min(nums[i..n-1]) is the smallest value among the elements from
index i to index n - 1.

An index i is called stable if its instability score is less than or equal to
k. Return the smallest stable index. If no such index exists, return -1.

Example 1:
    Input:  nums = [5,0,1,4], k = 3
    Output: 3
    Explanation: At index 3, max(nums[0..3]) = 5, min(nums[3..3]) = 4, so the
        instability score is 5 - 4 = 1, which is <= k = 3. This is the first
        such index.

Example 2:
    Input:  nums = [3,2,1], k = 1
    Output: -1
    Explanation: Every index has an instability score of 2, which exceeds
        k = 1.

Example 3:
    Input:  nums = [0], k = 0
    Output: 0
    Explanation: The instability score at index 0 is 0 - 0 = 0 <= k = 0.

Constraints:
    - 1 <= nums.length <= 100
    - 0 <= nums[i] <= 10^9
    - 0 <= k <= 10^9
"""
from typing import List
class Solution:
    def firstStableIndex(self, nums: List[int], k: int) -> int:
        n = len(nums)
        max_arrray = [0 for _ in range(n)]
        min_array = [0 for _ in range(n)]
        for i in range(n):
            if i == 0:
                max_arrray[i] = nums[i]
            else:
                max_arrray[i] = max(nums[i],max_arrray[i-1])

        for i in range(n-1,-1,-1):
            if i == n-1:
                min_array[i] = nums[i]
            else:
                min_array[i] = min(nums[i],min_array[i+1])

        for i in range(n):
            diff = max_arrray[i] - min_array[i]
            if(diff <= k):
                return i
        return -1


if __name__ == "__main__":
    tests = [
        ([5, 0, 1, 4], 3, 3),
        ([3, 2, 1], 1, -1),
        ([0], 0, 0),
        ([1, 1, 1, 1], 0, 0),
        ([9, 5, 3, 7], 100, 0),
    ]
    sol = Solution()
    for nums, k, expected in tests:
        result = sol.firstStableIndex(nums, k)
        status = "PASS" if result == expected else "FAIL"
        print(f"{status}: nums={nums}, k={k} -> got {result}, expected {expected}")
