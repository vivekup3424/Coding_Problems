from collections import Counter
from typing import List
class Solution:
    def countGood(self,nums:List[int],k:int)->int:
        res=cur=i=0
        count = Counter()
        for j in range(len(nums)):
            k -= count[A[j]]
            
