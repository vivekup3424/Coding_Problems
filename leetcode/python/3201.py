from typing import List
class Solution:
    def maximumLength(self, nums: List[int]) -> int:
        oddLength, evenLength, alternateLength = 0,0,0
        prev = -1
        #first odd
        for i in nums:
            if i % 2 == 1:
                oddLength+=1
            elif i % 2 == 0:
                evenLength+=1
            if prev == -1:
                prev = i%2
                alternateLength+=1
            if prev != -1 and prev%2==1:
                if i%2==0:
                    prev = 0
                    alternateLength+=1
            elif prev != -1 and prev%2==0:
                if i%2==1:
                    prev = 1
                    alternateLength+=1
        return max(oddLength,evenLength,alternateLength)
        