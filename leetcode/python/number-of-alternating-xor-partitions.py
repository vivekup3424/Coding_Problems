from functools import lru_cache
from typing import List
from collections import defaultdict

class Solution:
    def alternatingXOR(self, nums: List[int], target1: int, target2: int) -> int:
        prefix_xor:List[int] = []
        valueIndices: defaultdict[int,List[int]] = defaultdict(List[int])
        MOD = 10**9 + 7
        for i in range(len(nums)):
            if i == 0:
                prefix_xor.append(nums[i])
            else:
                prefix_xor.append(prefix_xor[i-1] ^ nums[i])
            valueIndices[prefix_xor[i]].append(i)


        @lru_cache
        def recurse(idx:int, isTargetOne: bool):
            if idx == -1:
                return 1
            answer = 0
            for i in range(idx, len(nums)):
                if idx-1 < 0:
                    value = prefix_xor[i]
                else:
                    value = prefix_xor[idx-1] ^ prefix_xor[i]
                if value == (target1 if isTargetOne else target2):
                    answer = int((answer + recurse(i+1,not isTargetOne))%MOD)
            return answer
        return recurse(0,True)