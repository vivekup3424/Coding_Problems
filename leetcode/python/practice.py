from typing import List

class Solution:
    def minimumCost(self, target: str, words: List[str], costs: List[int]) -> int:
        n = len(target)
        m = len(words)
        dp = [float('inf')] * (n + 1)
        dp[0] = 0
        
        for i in range(1, n + 1):
            for j in range(m):
                word = words[j]
                if len(word) <= i and target[i - len(word):i] == word:
                    dp[i] = min(dp[i], dp[i - len(word)] + costs[j])
        
        return dp[n] if dp[n] != float('inf') else -1
