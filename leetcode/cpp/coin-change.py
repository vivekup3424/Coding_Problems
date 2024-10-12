from typing import List

class Solution:
    def coinChange(self, coins: List[int], amount : int) -> int:
        n = len(coins)
        dp = [amount+1 for _ in range(n+1)]
        print(dp)
        dp[0] = 0
        for a in range(1,amount+1):
            for c in coins:
                if a - c >= 0:
                    dp[a] = min(dp[a], 1 + dp[a-c])
        print(dp)
        if dp[amount]!=amount+1:
            return dp[amount]
        else:
            return -1

