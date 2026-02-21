import java.util.*;
class Solution{
    public int[][] floodFill(int[][] image, int sr, int sc, int color){
        int origColor = image[sr][sc];
        if(origColor == color) return image;
        int[][] dirs = {{0,1},{0,-1},{1,0},{-1,0}};
        Deque<int[]> stack = new ArrayDeque<>();
        stack.push(new int[]{sr,sc});
        image[sr][sc] = color;
        while(!stack.isEmpty()){
            int[] cell = stack.pop();
            int row = cell[0], col = cell[1];
            for(int[] d : dirs){
                int nr = row + d[0];
                int nc = col + d[1];
                if(nr >= 0 && nr < image.length && nc >= 0 && nc < image[0].length && image[nr][nc] == origColor){
                    image[nr][nc] = color;
                    stack.push(new int[]{nr, nc});
                }
            }
        }
        return image;
    }
}