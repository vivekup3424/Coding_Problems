/*
 * 2812. Find the Safest Path in a Grid
 * https://leetcode.com/problems/find-the-safest-path-in-a-grid/
 *
 * You are given a 0-indexed 2D matrix `grid` of size n x n, where (r, c)
 * represents:
 *   - A cell containing a thief if grid[r][c] = 1
 *   - An empty cell if grid[r][c] = 0
 *
 * You are initially positioned at cell (0, 0). In one move, you can move to
 * any adjacent cell in the grid, including cells containing thieves.
 *
 * The safeness factor of a path between the source and destination cell is
 * defined as the minimum Manhattan distance to a thief along that path.
 *
 * Return the maximum safeness factor of all paths leading to cell (n-1, n-1).
 *
 * Note: An adjacent cell of cell (r, c) is one of the cells (r, c+1),
 * (r, c-1), (r+1, c), or (r-1, c) if it exists.
 *
 * Example 1:
 *   Input:  grid = [[1,0,0],[0,0,0],[0,0,1]]
 *   Output: 0
 *   Explanation: All paths from (0,0) to (2,2) pass adjacent to a thief.
 *
 * Example 2:
 *   Input:  grid = [[0,0,1],[0,0,0],[0,0,0]]
 *   Output: 2
 *   Explanation: The path (0,0) -> (1,0) -> (2,0) -> (2,1) -> (2,2) has
 *                a minimum Manhattan distance of 2 from any thief.
 *
 * Example 3:
 *   Input:  grid = [[0,0,0],[0,0,0],[0,0,0]]
 *   Output: 2
 *
 * Constraints:
 *   - 1 <= n <= 400
 *   - grid[i][j] is either 0 or 1
 *   - There is at least one thief in the grid
 */

import java.util.ArrayDeque;
import java.util.Queue;

class Solution{
    public void bfs(int[][] grid, [][] safeness, boolean[][] visited){
        int rows = grid.length;
        Queue<int[]> q = new ArrayDeque<>();
        for(int i = -)
    }
    public int maximumSafesnessInGried(int[][] grid){
        int rows = grid.length, cols = grid[0].length;

    }
}