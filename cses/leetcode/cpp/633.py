import math
class Solution:
    def judgeSquareSum(self, c: int) -> bool:
        squareSet = set()
        for x in range(int(math.sqrt(c)) + 1):
            squareSet.add(x * x)

        for aSquare in squareSet:
            bSquare = c - aSquare
            if bSquare in squareSet:
                return True
        return False