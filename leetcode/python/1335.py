from collections import deque
from typing import Deque


class Solution:
    def minDifficulty(self, jobDifficulty: List[int], d: int) -> int:
        n = len(jobDifficulty)
        highestTillNow = [0] * n
        for i in range(n):
            if i == 0:
                highestTillNow[i] = jobDifficulty[i]
            else:
                highestTillNow[i] = max(highestTillNow[i - 1], jobDifficulty[i])
        print(highestTillNow)
        if d > n:
            return -1
