from typing import List
from functools import cache
class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        n = len(nums)
        @cache
        def recurse(i,sum):
            if i == n:
                return sum == target
            else:
                return recurse(i+1,sum+nums[i]) + recurse(i+1,sum-nums[i])
        return recurse(0,0)


class SolutionDP:
    def findTargetSumWays(self,nums:List[int],target:int)->int:
        n = len(nums)
        memo = {}
        def recurse(i,sum):
            if (i,sum) in memo:
                return memo[(i,sum)]
            elif i == n:
                memo[(i,sum)] = sum == target
            else:
                memo[(i,sum)] = recurse(i+1,sum+nums[i]) + recurse(i+1,sum-nums[i])
            return memo[(i,sum)]
        return recurse(0,0)

#after taking a break of half an hour, I think now I am getting 
#on how to solve this using some clever trick and past experience

# suppose I had a subset of array choosen s.t sum(subset) = x
# and total sum of the array = S, and target = t
# now sum(x`) + sum(x) = S+t
#fuck tihs, I am moving on

nums = [35,37,9,29,36,0,44,32,44,13,2,37,14,21,41,36,9,23,41,17]
target = 42
# nums = [1,1,1,1,1]
# target = 3
print(SolutionDP().findTargetSumWays(nums,target))