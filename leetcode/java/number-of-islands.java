/*
 * 200. Number of Islands
 * https://leetcode.com/problems/number-of-islands/
 *
 * Given an m x n 2D binary grid grid which represents a map of '1's (land)
 * and '0's (water), return the number of islands.
 *
 * An island is surrounded by water and is formed by connecting adjacent
 * lands horizontally or vertically. You may assume all four edges of the
 * grid are all surrounded by water.
 *
 * Example 1:
 *   Input:  grid = [
 *     ["1","1","1","1","0"],
 *     ["1","1","0","1","0"],
 *     ["1","1","0","0","0"],
 *     ["0","0","0","0","0"]
 *   ]
 *   Output: 1
 *
 * Example 2:
 *   Input:  grid = [
 *     ["1","1","0","0","0"],
 *     ["1","1","0","0","0"],
 *     ["0","0","1","0","0"],
 *     ["0","0","0","1","1"]
 *   ]
 *   Output: 3
 *
 * Constraints:
 *   - m == grid.length
 *   - n == grid[i].length
 *   - 1 <= m, n <= 300
 *   - grid[i][j] is '0' or '1'.
 */
class Solution {
    private void dfs(char[][] grid, boolean[][] visited, int X, int Y){
        int rows = grid.length, cols = grid[0].length;
        if(X < 0 || X >= rows || Y < 0 || Y >= cols) return;
        if(visited[X][Y] || grid[X][Y]== '0')return;
        visited[X][Y] = true;
        dfs(grid, visited, X-1, Y);
        dfs(grid, visited, X+1, Y);
        dfs(grid, visited, X, Y-1);
        dfs(grid, visited, X, Y+1);
    }
    public int numIslands(char[][] grid) {
        int count = 0;
        int rows = grid.length, cols = grid[0].length;
        boolean[][] visited = new boolean[rows][cols];
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(visited[i][j]==false && grid[i][j] == '1'){
                    dfs(grid,visited,i,j);
                    count++;
                }
            }
        }
        return count;
    }
}
