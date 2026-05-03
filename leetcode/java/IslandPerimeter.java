import java.util.LinkedList;
import java.util.Queue;

public class IslandPerimeter {
    public int naiveApproach(int[][] grid) {
        if (grid.length == 0) return 0;
        int m = grid.length, n = grid[0].length;
        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    count += (i + 1 >= m || grid[i + 1][j] == 0) ? 1 : 0;
                    count += (i - 1 < 0  || grid[i - 1][j] == 0) ? 1 : 0;
                    count += (j + 1 >= n || grid[i][j + 1] == 0) ? 1 : 0;
                    count += (j - 1 < 0  || grid[i][j - 1] == 0) ? 1 : 0;
                }
            }
        }
        return count;
    }

    // Each land cell contributes 4 edges; subtract 2 for each shared edge with
    // an already-visited neighbor (only check up and left to avoid double-counting).
    public int naiveApproach2(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    count += 4;
                    if (i > 0 && grid[i - 1][j] == 1) count -= 2;
                    if (j > 0 && grid[i][j - 1] == 1) count -= 2;
                }
            }
        }
        return count;
    }

    public int dfs(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        boolean[][] visited = new boolean[m][n];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 1)
                    return dfsHelper(grid, visited, i, j, m, n);
        return 0;
    }

    private int dfsHelper(int[][] grid, boolean[][] visited, int i, int j, int m, int n) {
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0) return 1;
        if (visited[i][j]) return 0;
        visited[i][j] = true;
        return dfsHelper(grid, visited, i + 1, j, m, n)
             + dfsHelper(grid, visited, i - 1, j, m, n)
             + dfsHelper(grid, visited, i, j + 1, m, n)
             + dfsHelper(grid, visited, i, j - 1, m, n);
    }

    public int bfs(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        boolean[][] visited = new boolean[m][n];
        int[][] dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        Queue<int[]> queue = new LinkedList<>();
        outer:
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 1) { visited[i][j] = true; queue.offer(new int[]{i, j}); break outer; }

        int perimeter = 0;
        while (!queue.isEmpty()) {
            int[] cell = queue.poll();
            for (int[] d : dirs) {
                int r = cell[0] + d[0], c = cell[1] + d[1];
                if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 0) {
                    perimeter++;
                } else if (!visited[r][c]) {
                    visited[r][c] = true;
                    queue.offer(new int[]{r, c});
                }
            }
        }
        return perimeter;
    }
}
