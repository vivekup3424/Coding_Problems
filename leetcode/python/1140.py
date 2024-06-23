from typing import List
class Solution:
    def stoneGameII(self, piles: List[int]) -> int:
        n = len(piles)

        def f(p,i,m):
            if i == n:
                return 0
            res = 0
            if p==0:
                res = -1
            else:
                res = 100000
            s = 0
            for x in range(1,min(2*m,n-1)+1):
                s += piles[i+x-1]
                if p == 0:
                    res = max(res,s+f(1,i+x,max(m,x)))
                elif p==1:
                    res = min(res,s+f(0,i+x,max(m,x)))
        
        f(0,0,1)