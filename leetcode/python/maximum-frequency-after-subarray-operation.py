from collections import Counter
from typing import List
class Solution:
    def maxFrequency(self, nums: List[int], k: int) -> int:
        #get the element with most frequency for now
        freq = Counter(nums)
        twoMostCommonElements = freq.most_common(2)
        if twoMostCommonElements[0][0] == k:
            