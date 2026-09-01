"""
3568. Minimum Moves to Clean the Classroom
https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/

A student volunteer must clean litter from an m x n grid classroom. Grid
cells contain:
    'S': Starting position
    'L': Litter to collect
    'R': Reset area (restores energy to maximum)
    'X': Impassable obstacle
    '.': Empty space

The student starts with energy units and consumes 1 energy per adjacent
move. When energy reaches 0, they must be on 'R' to continue. Return the
minimum moves to collect all litter, or -1 if impossible.

Example 1:
    Input:  classroom = ["S.", "XL"], energy = 2
    Output: 2
    Explanation: Path (0,0)->(0,1)->(1,1), collecting litter in 2 moves.

Example 2:
    Input:  classroom = ["LS", "RL"], energy = 4
    Output: 3
    Explanation: Path (0,1)->(0,0)->(1,0)->(1,1), using reset at R.

Example 3:
    Input:  classroom = ["L.S", "RXL"], energy = 3
    Output: -1
    Explanation: No valid path exists.

Constraints:
    - 1 <= m, n <= 20
    - At most 10 litter cells
    - Exactly one starting position
    - 1 <= energy <= 50
"""
from typing import List
class Solution:
    def minimumMoves(self, classroom: List[str], energy: int) -> int:
        rows, cols = len(classroom), len(classroom[0])
        max_energy = energy
        litter_index = {}
        start = None
        for r in range(rows):
            for c in range(cols):
                ch = classroom[r][c]
                if ch == 'S':
                    start = (r,c)
                elif ch == 'L':
                    litter_index[(r,c)] = len(litter_index)

        total_litter = len(litter_index)
        full_mask = (1 << total_litter) - 1 if total_litter else 0

        if start is None:
            return -1
        if total_litter == 0:
            return 0
