from typing import List
class Solution:
    def minCost(self, n: int, cost: List[List[int]]) -> int:
        def recurse(i,j,k):
            if i == (n/2 -1):
                return cost[i][j] + cost[i+1][k]
            else:
                minChoice = 1000
                for new_j in range(2):
                    for new_k in range(2):
                        if(new_j != j and new_k != k and new_j != new_k):
                            minChoice = min(minChoice,recurse(i+1,new_j,new_k))
                return cost[i][j]+cost[n-1-i][k]+minChoice
        return min(recurse(0,1,2), recurse(0,0,1), recurse(0,0,2), recurse(0,1,0),recurse(0,2,0),recurse(0,2,1)) 