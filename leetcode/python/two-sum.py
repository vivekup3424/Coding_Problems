from typing import List
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        value_index = {} #mapping of value to its index
        for i in range(len(nums)):
            complement = target - nums[i]
            if complement in value_index:
                return [i, value_index[complement]]
            else:
                value_index[nums[i]] = i
        return []