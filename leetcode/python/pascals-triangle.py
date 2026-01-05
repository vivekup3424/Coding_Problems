from typing import List
class Solution:
    def generate(self, numRows: int) -> List[List[int]]:
        answer: List[List[int]] = [[]]
        for i in range(numRows):
            if i == 0:
                answer.append([1])
            else:
                temp : List[int] = []
                for j in range(i+1):
                    value = 0
                    if j == 0 or j == i:
                        value = 1
                    else:
                        value = answer[-1][j] + answer[-1][j-1]
                    temp.append(value)
                answer.append(temp)
        return answer
