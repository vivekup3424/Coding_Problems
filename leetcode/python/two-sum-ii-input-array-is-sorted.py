from typing import List
class Solution:
    def twoSum(self,numbers: List[int], target: int) -> List[int]:
        first, last = 0, len(numbers)-1
        while first < last:
            sum = numbers[first] + numbers[last]
            if sum > target:
                last-=1
            if sum < target:
                first+=1
            if sum == target:
                return [first+1,last+1]
        return []