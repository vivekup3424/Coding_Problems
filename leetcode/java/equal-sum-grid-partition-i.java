class Solution{
    int findSum(int[][] matrix, int row_i, int row_j, int col_i, int col_j){
        int sum = 0;
        for (int i = row_i; i <=row_j; i++) {
            for (int j = col_i; j <= col_j; j++) {
               sum += matrix[i][j];
            }
        }
        return sum;
    }
    public boolean canPartitionHorizontally(int[][] grid){
        //we are making horizontal partition row-wise
        for(int i = 1; i < grid.length; i++){
            int sum1 = findSum(grid, 0, i-1, 0, grid[0].length-1);
            int sum2 = findSum(grid, i, grid.length-1, 0, grid[0].length-1);
            if(sum1==sum2) return true;
        }
        return false;
    }
    public boolean canPartitionVertically(int[][] grid){
        
    }
}