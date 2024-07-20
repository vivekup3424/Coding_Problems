from typing import List
class Solution:
    def restoreMatrix(self, rowSum: List[int], colSum: List[int]) -> List[List[int]]:
        rowLength = len(rowSum)
        colLength = len(colSum)
        currentRowSum = [0] * rowLength
        currentColumnSum = [0] * colLength
        matrix = [[0 for _ in range(rowLength)] for _ in range(colLength)]
        for i in range(rowLength):
            for j in range(colLength):
                matrix[i][j] = min(rowSum[i] - currentRowSum[i],
                                colSum[j] - currentColumnSum[j])
                currentRowSum[i] += matrix[i][j]
                currentColumnSum[j] += matrix[i][j]
        return matrix
