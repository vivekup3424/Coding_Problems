from typing import List
class Solution:
    def longestOnes(self, nums: List[int], maxZeroesAllowed: int) -> int:
        maxPossibleOnes = 0
        currentOnes, currentZeroes= 0,0
        l, r, n = 0,0, len(nums)
        while r < n:
            if nums[r]==1:
                currentOnes+=1
            else:
                currentZeroes+=1
            while currentZeroes > maxZeroesAllowed:
                if nums[l] == 0:
                    currentZeroes-=1
                l+=1
            
            currentPossibleOnes = currentOnes + currentZeroes
            maxPossibleOnes = max(maxPossibleOnes,currentPossibleOnes)
        return maxOnes