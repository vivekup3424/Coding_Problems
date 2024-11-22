from typing import List


class Solution:
    def generateComplement(self, row):
        complement = []
        for i in row:
            if i:
                complement.append(0)
            else:
                complement.append(1)
        return complement

    def maxEqualRowsAfterFlips(self, matrix: List[List[int]]) -> int:
        """We'll loop over each row in the given matrix to determine which approach is best. For each row, we count the number of other rows in the matrix that are exactly the same and that are exactly opposite. The highest count across all rows will be our answer."""
        maxCount = 1
        for i in range(len(matrix)):
            row = matrix[i]
            complement = self.generateComplement(row)
            count = 0
            for j in range(i, len(matrix)):
                if row == matrix[i]:
                    count += 1
                elif complement == matrix[i]:
                    count += 1
            maxCount = max(maxCount, count)
        return maxCount
