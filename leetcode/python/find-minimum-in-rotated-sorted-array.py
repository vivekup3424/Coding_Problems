from typing import List
class Solution:
    def findMinimumInSortedArray(self, numbers: List[int]):
        left, right = 0, len(numbers)-1
        while left < right:
            mid = (left+right)//2
            if numbers[mid] < numbers[right]:
                right = mid
            elif numbers[mid] > numbers[right]:
                left = mid + 1
        return left