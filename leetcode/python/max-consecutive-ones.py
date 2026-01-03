from typing import List
class Solution:
    def findMaxConsecutiveOnes(self, nums: List[int]) -> int:
        maximum = 0
        result = 0
        for i in nums:
            if i == 1:
                result += 1
                maximum = max(maximum,result)
            else:
                result = 0
        return maximum