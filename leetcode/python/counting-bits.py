from typing import List
class Solution:
    def countBits(self, n : int)-> List[int]:
        dp: List[int] = [0 for _ in range(0,n+1)]
        for i in range(1,n+1):
            dp[i] = dp[int(i/2)] + (i%2)
        return dp