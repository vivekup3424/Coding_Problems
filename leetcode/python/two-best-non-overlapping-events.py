from typing import List


# cleary this problem is of dp
class Solution:
    def maxTwoEvents(self, events: List[List[int]]) -> int:
        sorted()
        maxTime = 0
        for startTime, endTime, _ in events:
            maxTime = max(maxTime, max(startTime, endTime))
        dp = [[0 for _ in range(maxTime)] for _ in range(maxTime)]
        print(dp)


events = [[1, 3, 2], [4, 5, 2], [2, 4, 3]]
Solution().maxTwoEvents(events)
