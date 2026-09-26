import numpy as np


class Solution:
    def longestValidSubarray(self, nums: list[int], k: int) -> int:
        n = len(nums)

        prefix = [0] * (n + 1)
        for t in range(1, n + 1):
            prefix[t] = (prefix[t - 1] + nums[t - 1]) % k

        INF = n + 1
        earliest = np.full(k, INF, dtype=np.int64)
        latest = np.full(k, -1, dtype=np.int64)
        for t in range(n + 1):
            r = prefix[t]
            if earliest[r] == INF:
                earliest[r] = t
            latest[r] = t

        ans = 0

        # Condition A: sum already divisible by k, no negation needed.
        for j in range(1, n + 1):
            r = prefix[j]
            if earliest[r] < j:
                ans = max(ans, j - int(earliest[r]))

        # Condition B: negate exactly one element at position m.
        idx = np.arange(k)
        for m in range(1, n + 1):
            d = (2 * nums[m - 1]) % k
            shifted_latest = latest[(idx + d) % k]
            valid = (earliest < m) & (shifted_latest >= m)
            if valid.any():
                candidate = (shifted_latest - earliest)[valid].max()
                if candidate > ans:
                    ans = int(candidate)

        return ans
