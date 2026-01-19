from typing import List
class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        stack:List[int]= [] #indices
        n = len(temperatures)
        answer = [0 for _ in range(n)]
        for i in range(n):
            while len(stack) > 0 and temperatures[i] > temperatures[stack[-1]]:
                idx = stack[-1]
                gap = i - idx
                stack.pop()
                answer[idx] = gap
            stack.append(i)
        return answer