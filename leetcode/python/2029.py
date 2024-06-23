from typing import List
import collections
class Solution:
 def stoneGameIX(self, stones):
        cnt = collections.Counter(a % 3 for a in stones)
        if min(cnt[1], cnt[2]) == 0:
            return max(cnt[1], cnt[2]) > 2 and cnt[0] % 2 > 0
        return abs(cnt[1] - cnt[2]) > 2 or cnt[0] % 2 == 0
        
if __name__ == "__main__":
    sol = Solution()
    stones = [2, 1, 1, 1, 2, 3, 3]
    sol.stoneGameIX(stones)

