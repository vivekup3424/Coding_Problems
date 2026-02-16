import java.util.*;

class Solution{
    public int equalPairs(int[][] grid){
        int rows = grid.length, cols = grid[0].length;
        Map<Integer,String> rowsPattern = new HashMap<>();
        Map<String,List<Integer>> ColPatternIndices = new HashMap<>();
        for(int i = 0; i < rows; i++){
            StringBuilder temp = new StringBuilder();
            for(int j = 0; j < cols; j++){
                temp.append(grid[i][j]);
            }
            rowsPattern.put(i, temp.toString());
        }
        for(int j = 0; j < cols; j++){
            StringBuilder temp = new StringBuilder();
            for(int i = 0; i < rows; i)
        }
    }
}