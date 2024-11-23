"""Find the contiguous subarray within an array, A of length N which has the largest sum."""


class Solution:
    def maxSubArraySum(self, arr):
        max_sum, current_sum = arr[0], 0
        for num in arr:
            current_sum += num
            if current_sum < 0:
                current_sum = 0
            max_sum = max(max_sum, current_sum)
        return max_sum


if __name__ == "__main__":
    arr = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
    print(Solution().maxSubArraySum(arr))
