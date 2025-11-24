from typing import List
class Solution:
    def prefixesDivBy5(self, nums: List[int]) -> List[bool]:
        result: List[bool] = []
        current_number = 0
        for num in nums:
            current_number = (current_number << 1) | num
            result.append(current_number % 5 == 0)
        return result