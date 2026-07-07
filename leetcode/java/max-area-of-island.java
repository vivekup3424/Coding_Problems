/*
 * 695. Max Area of Island
 * https://leetcode.com/problems/max-area-of-island/
 *
 * You are given an m x n binary matrix grid. An island is a group of 1's
 * (representing land) connected 4-directionally (horizontal or vertical.)
 * You may assume all four edges of the grid are surrounded by water.
 *
 * The area of an island is the number of cells with a value 1 in the
 * island.
 *
 * Return the maximum area of an island in grid. If there is no island,
 * return 0.
 *
 * Example 1:
 *   Input:  grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],
 *                    [0,0,0,0,0,0,0,1,1,1,0,0,0],
 *                    [0,1,1,0,1,0,0,0,0,0,0,0,0],
 *                    [0,1,0,0,1,1,0,0,1,0,1,0,0],
 *                    [0,1,0,0,1,1,0,0,1,1,1,0,0],
 *                    [0,0,0,0,0,0,0,0,0,0,1,0,0],
 *                    [0,0,0,0,0,0,0,1,1,1,0,0,0],
 *                    [0,0,0,0,0,0,0,1,1,0,0,0,0]]
 *   Output: 6
 *   Explanation: The answer is not 11, because the island must be
 *   connected 4-directionally.
 *
 * Example 2:
 *   Input:  grid = [[0,0,0,0,0,0,0,0]]
 *   Output: 0
 *
 * Constraints:
 *   - m == grid.length
 *   - n == grid[i].length
 *   - 1 <= m, n <= 50
 *   - grid[i][j] is either 0 or 1.
 */
class Solution {
    private int dfs(int[][] grid, boolean[][] visited, int X, int Y){
        int rows = grid.length, cols = grid[0].length;
        if(X < 0 || X >= rows || Y < 0 || Y >= cols) return 0;
        if(visited[X][Y] || grid[X][Y]==0) return 0;
        visited[X][Y] = true;
        int sum = 1;
        sum += dfs(grid, visited, X-1, Y);
        sum += dfs(grid, visited, X+1, Y);
        sum += dfs(grid, visited, X, Y-1);
        sum += dfs(grid, visited, X, Y+1);
        return sum;
    }
    public int maxAreaOfIsland(int[][] grid) {

    }
}
1