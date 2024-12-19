class Solution:
    def spirallyTraverse(self,matrix):
        rows = len(matrix)
        cols = len(matrix[0])
        directions = [(0,1),(1,0),(0,-1),(-1,0)]
        ans = []
        while True:
            for d in directions:


