public class RotateImage {

    public void rotate(int[][] matrix){
        //given it's a n*n matrix, I can transpose it easily in-place
        //using swap(matrix[i][j],matrix[j][i]) kind of operation
        int n = matrix.length;
        //row-reverse
        int topRow = 0, bottomRow = n-1;
        while(topRow < bottomRow){
            for(int j = 0; j < n; j++){
                int temp = matrix[topRow][j];
                matrix[topRow][j] = matrix[bottomRow][j];
                matrix[bottomRow][j] = temp;
            }
            topRow++;
            bottomRow--;
        }
        //transpose
        for(int i = 0; i < n; i++){
            for(int j = 0; j < i; j++){
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }
        return;
    }
}