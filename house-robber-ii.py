from typing import List


class Solution:
    def rob(self, nums: List[int]) -> int:
        if not nums:
            return 0
        elif len(nums) == 1:
            return nums[0]
        elif len(nums) == 2:
            return max(nums[0], nums[1])
        else:
            return max(self.rob(nums[1:]), self.rob(nums[:-1]))


class Solution2:
    def rob(self, nums: List[int]) -> int:
        dp1 = [0] * (len(nums) - 1)
        dp2 = [0] * (len(nums) - 1)
        for i in range(0, len(nums) - 1):
            if i == 0:
                dp1[i] = nums[0]
            elif i == 1:
                dp1[i] = max(nums[0], nums[1])
            else:
                dp1[i] = max(dp1[i - 2] + nums[i], dp1[i - 1])
        for i in range(1, len(nums)):
            if i == 1:
                dp2[i - 1] = nums[1]
            elif i == 2:
                dp2[i - 1] = max(nums[1], nums[2])
            else:
                dp2[i - 1] = max(dp2[i - 2] + nums[i], dp2[i - 1])
        return max(dp1[-1], dp2[-1])
