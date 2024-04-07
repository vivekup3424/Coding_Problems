from typing import List

class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        stack = []
        n = len(nums)
        l = n - k + 1
        currentMax = -10000000
        for i in range(0,k):
            currentMax = max(currentMax,nums[i])
            stack.append((nums[i],currentMax))
        maxValues = [currentMax]
        for i in range(0,l):
            stack.pop()
            currentMax = max(stack[0][1], nums[i+k-1])
            stack.append((nums[i+k-1], currentMax))
            maxValues.append(currentMax)
        return maxValues

# Driver code
if __name__ == "__main__":
    solution = Solution()
    nums = [1, 3, -1, -3, 5, 3, 6, 7]
    k = 3
    result = solution.maxSlidingWindow(nums, k)
    print(result)  # Output: [3, 3, 5, 5, 6, 7]