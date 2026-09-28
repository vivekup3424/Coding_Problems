"""
2462. Total Cost to Hire K Workers
https://leetcode.com/problems/total-cost-to-hire-k-workers/

You are given a 0-indexed integer array costs where costs[i] is the cost of
hiring the ith worker.

You are also given two integers k and candidates. We want to hire exactly k
workers according to the following rules:

    - You will run k sessions and hire exactly one worker in each session.
    - In each hiring session, choose the worker with the lowest cost from
      either the first candidates workers or the last candidates workers.
      Break the tie by the smallest index. If there are fewer than candidates
      workers remaining in both the first and last parts, consider all the
      remaining workers as candidates.
    - If there are multiple workers with the lowest cost among the chosen
      candidates, choose the one with the smallest index.

The total cost is the sum of the costs of the k workers you hired.

Return the total cost to hire exactly k workers.

Example 1:
    Input:  costs = [17,12,10,2,7,2,11,20,8], k = 3, candidates = 4
    Output: 11
    Explanation: We hire 3 workers in total. The total cost is initially 0.
        - In the first hiring round we choose from candidates
          [17,12,10,2] and [11,20,8]. The lowest cost is 2, and we break the
          tie by the smallest index, which is 3. The total cost = 0 + 2 = 2.
        - In the second hiring round we choose from candidates
          [17,12,10,7] and [11,20,8]. The lowest cost is 7, and we break the
          tie by the smallest index, which is 4. The total cost = 2 + 7 = 9.
        - In the third hiring round we choose from candidates [17,12,10] and
          [11,20,8]. The lowest cost is 8, and we break the tie by the
          smallest index, which is 8. The total cost = 9 + 8 = 17.
        The total cost is 11.

Constraints:
    - 1 <= costs.length <= 10^5
    - 1 <= costs[i] <= 10^5
    - 1 <= k, candidates <= costs.length
"""
from typing import List
import heapq

class Solution:
    def totalCost(self, costs: List[int], k: int, candidates: int) -> int:
        minheap1, minheap2, n = [], [], len(costs)
        i, j = 0, n - 1
        cost = 0
        for _ in range(k):
          while len(minheap1) < candidates and i <= j:
            heapq.heappush(minheap1, costs[i])
            i += 1
          while len(minheap2) < candidates and i <= j:
            heapq.heappush(minheap2, costs[j])
            j -= 1
          if minheap2 and (not minheap1 or minheap2[0] < minheap1[0]):
            cost += heapq.heappop(minheap2)
          else:
            cost += heapq.heappop(minheap1)
        return cost


