// Question (LeetCode 463):
// You are given a row x col grid representing a map where grid[i][j] = 1 is land and
// grid[i][j] = 0 is water. The grid is surrounded by water, and there is exactly one island
// (no lakes). Return the perimeter of the island.
//
// Example 1:
//   Input:  grid = [[0,1,0,0],
//                   [1,1,1,0],
//                   [0,1,0,0],
//                   [1,1,0,0]]
//   Output: 16
//
// Example 2:
//   Input:  grid = [[1]]
//   Output: 4
//
// Example 3:
//   Input:  grid = [[1,0]]
//   Output: 4
//
// Constraints:
//   - row == grid.length, col == grid[i].length
//   - 1 <= row, col <= 100
//   - grid[i][j] is 0 or 1
//   - There is exactly one island in the grid

class Solution {
    public int islandPerimeter(int[][] grid) {
        int rows = grid.length, cols = grid[0].length;
        int perimeter = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if(grid[i][j] == 1){
                    if(i==0 || grid[i-1][j] == 0) perimeter++;
                    if(j==0 || grid[i][j-1] == 0) perimeter++;
                    if(i==rows-1 || grid[i+1][j] == 0) perimeter++;
                    if(j==cols-1 || grid[i][j+1] == 0) perimeter++;
                }
            }
        }
        return perimeter;
    }
}