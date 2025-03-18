from typing import List
from collections import defaultdict
class Solution:
    def longestNiceSubarray(self, nums: List[int]) -> int:
        freqHashmap = defaultdict(int)
        i, j, n, maxLen, numBitWithMultipleOccurence = 0, 0, len(nums), 0, 0
        while j < n:
            for k in range(64):
                if nums[j] & (1 << k):
                    freqHashmap[k] += 1
                    if freqHashmap[k] > 1:
                        numBitWithMultipleOccurence += 1
            while numBitWithMultipleOccurence > 0:
                for k in range(64):
                    if nums[i] & (1 << k):
                        freqHashmap[k] -= 1
                        if freqHashmap[k] == 1:
                            numBitWithMultipleOccurence -= 1
                i += 1
            maxLen = max(maxLen, j - i + 1)
            j += 1
        return maxLen
