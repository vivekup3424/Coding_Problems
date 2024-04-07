class Solution:
    def findMaxConsecutiveOnes(self, nums: List[int]) -> int:
        currentLength, maxLength = 0,0
        for i in nums:
            if i == 1:
                currentLength+=1
            elif i==0:
                currentLength = 0
            maxLength = max(maxLength, currentLength)
        return maxLength
