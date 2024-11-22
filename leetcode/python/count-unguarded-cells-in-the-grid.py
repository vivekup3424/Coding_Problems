from typing import List
from enum import Enum, auto

class Value(Enum):
    UNGAURDED = auto()
    GAURDED = auto()
    GUARD = auto()
    BLOCKED = auto()


class Solution:
    def countUnguarded(
        self, rows: int, cols: int, guards: List[List[int]], walls: List[List[int]]
    ) -> int:
        matrix = [[Value.UNGAURDED for _ in range(cols)] for _ in range(rows)]
        print(matrix)  # debug
        
        for guard in guards:
            print(f"guard = {guard}")
            x, y = guard[0], guard[1]  # debug
            matrix[x][y] = Value.GUARD
        for wall in walls:
            print(f"wall = {wall}")  # debug
            x, y = wall[0], wall[1]
            matrix[x][y] = Value.BLOCKED
        for guard in guards:
            x,y = guard[0],guard[1]
            #go left
            x_left = x
            while x_left >= 0 and matrix[x_left][y] is not in (Value.BLOCKED,):
                pass
        count = 0
        for i in range(rows):
            for j in range(cols):
                if matrix[i][j] == Value.UNGAURDED:
                    count += 1
        return count
