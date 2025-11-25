from typing import List
class Solution:
    def nextPermutation(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        
        :param self: Description
        :param nums: Description
        :type nums: List[int]
        """
        n = len(nums)
        i = n - 2

        while i >= 0 and nums[i] >= nums[i+1]:
            i -= 1
        first, last = i + 1, n - 1
        while first < last:
            nums[first], nums[last] = nums[last], nums[first]
            first += 1
            last -= 1
        if i >= 0:
            for j in range(i+1,n):
                if nums[j] > nums[i]:
                    nums[i], nums[j] = nums[j], nums[i]
                    return

if __name__ == "__main__":
    sol = Solution()
    arr = [1,2,3,8,7,6]
    print("Original array:", arr)
    sol.nextPermutation(arr)
    print("Next permutation:", arr)
    print("Address= ", hex(id(arr)))