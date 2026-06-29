import java.util.ArrayDeque;
import java.util.List;
import java.util.Queue;

class Solution{
    public int islandPerimeter(int[][] grid){
        int rows = grid.length, cols = grid[0].length;
        Queue<List<Integer,Integer>> q = new ArrayDeque<>();
        int perimeter = 0;
        int[] dirX = new int[]{0,1,0,-1};
        int[] dirY = new int[]{1,0,-1,0};
        boolean[][] visited = new boolean[rows][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
               visited[i][j] = false;
            }
        }
        q.add()
    }
}