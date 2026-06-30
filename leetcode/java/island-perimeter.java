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
                    if(i==0 || grid[i-1][j] == 0) perimeter++;
                }
            }
        }
    }
}