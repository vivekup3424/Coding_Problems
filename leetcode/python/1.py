from typing import List


class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        # make a hashmap to store element and their index
        hashmap = {}
        for i, num in enumerate(nums):
            complement = target - num
            if complement in hashmap:
                return [hashmap[complement], i]
            hashmap[num] = i


if __name__ == "__main__":
    nums = [2, 7, 11, 15]
    target = 9
    solution = Solution()
    result = solution.twoSum(nums, target)
    print(result)

