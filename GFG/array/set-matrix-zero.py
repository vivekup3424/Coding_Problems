class Solution:
    def setMatrixZeroes(self, mat): 
        rowIndices = set()
        colIndices = set()
        rows = len(mat)
        cols = len(mat[0])
        for i in range(rows):
            for j in range(cols):
                if mat[i][j] == 0:
                    rowIndices.add(i)
                    colIndices.add(j)
        for i in range(rows):
            for j in range(cols):
                if i in rowIndices or j in colIndices:
                    mat[i][j] = 0

class Solution2:
    def setMatrixZeroes(self, mat):
        rows, cols = len(mat), len(mat[0])
        greatestElement = max(max(row) for row in mat) + 1
        for i in range(rows):
            for j in range(cols):
                if mat[i][j] == 0:
                    mat[0][j] = greatestElement  # Mark column
                    mat[i][0] = greatestElement  # Mark row
        # Zero out rows and columns except the first row
        for i in range(1, rows):
            if mat[i][0] == greatestElement:
                for j in range(cols):

        # Zero out columns except the first column
        for j in range(1, cols):
            if mat[0][j] == greatestElement:
                for i in range(rows):
                    mat[i][j] = 0
        # Handle the first row and column separately
        if mat[0][0] == greatestElement:
            for i in range(rows):
                mat[i][0] = 0
        if greatestElement in mat[0]:
            for j in range(cols):
                mat[0][j] = 0
