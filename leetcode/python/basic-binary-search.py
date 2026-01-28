from typing import List
class Solution:
    def linearSearch(self, values: List[int], target: int):
        for index, value in enumerate(values):
            if target == value:
                return index
        return -1
    
    def binarySearch(self, values: List[int], target: int):
        left, right = 0, len(values)-1
        while left <= right:
            mid = (left+right)//2
            if values[mid] == target:
                return mid
            elif values[mid] > target:
                right = mid-1
            else:
                left = mid+1
        return -1