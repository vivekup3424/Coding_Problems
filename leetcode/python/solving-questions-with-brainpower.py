from typing import List

class Solution:
    def mostPoints(self, questions: List[List[int]])->int:
        n = len(questions)
        def recurse(i):
            if i >= n:
                return 0
            else:
                return max((questions[i][0] + recurse(i+questions[i][1]+1)), (recurse(i+1)))
        return recurse(0)