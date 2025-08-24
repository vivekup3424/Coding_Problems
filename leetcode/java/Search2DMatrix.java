public class Search2DMatrix {
    public boolean searchMatrix(int[][] matrix, int target){
        if(matrix == null || matrix.length == 0 || matrix[0].length == 0) return false;
        int rows = matrix.length, cols = matrix[0].length;
        int left = 0, right = rows * cols - 1;
        while(left <= right){
            int mid = left + (right - left) / 2;
            if(matrix[mid / cols][mid % cols] == target) return true;
            if(matrix[mid / cols][mid % cols] < target) left = mid + 1;
            else right = mid - 1;
        }
        return false;
    }
}
