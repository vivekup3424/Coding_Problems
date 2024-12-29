from typing import List
class Solution:
    def minCostClimbingStairs(self,cost:List[int]):
        cost.append(0)
        n = len(cost)
        memo = [-1 for _ in range(n)]
        def recurse(i:int)->int:
            if memo[i] != -1:
                return memo[i]
            if i==0:
                memo[i] = cost[0]
            elif i==1:
                memo[i] = cost[1]
            else:
                memo[i] = min(recurse(i-1),recurse(i-2)) + cost[i]
            return memo[i]
        return recurse(n-1)
    def bottomUp(self,cost:List[int])->int:
        cost.append(0)
        n = len(cost)
        dp = [-1]*n
        for i in range(n):
            if i==0 or i == 1:
                dp[i]=cost[i]
            else:
                dp[i] = min(dp[i-1],dp[i-2]) + cost[i]
        return dp[n-1]

cost = [10,15,20]
print(Solution().minCostClimbingStairs(cost))