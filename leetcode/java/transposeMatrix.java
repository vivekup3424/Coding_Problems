class transposeMatrix {

    // For square matrix in-place transpose
    public void getTranspose(int matrix[][]){
        int rows = matrix.length, cols = matrix[0].length;
        if (rows != cols) {
            System.out.println("In-place transpose only works for square matrices!");
            return;
        }
        for(int i = 0; i < rows; i++){
            for(int j = i + 1; j < cols; j++){ // Start j from i+1 to avoid swapping twice
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }
    }
    
    // For any matrix (returns new transposed matrix)
    public int[][] getTransposeNew(int matrix[][]){
        int rows = matrix.length, cols = matrix[0].length;
        int[][] transposed = new int[cols][rows];
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                transposed[j][i] = matrix[i][j];
            }
        }
        return transposed;
    }
    
    public void printMatrix(int[][] matrix){
        for(int i = 0; i < matrix.length; i++){
            for(int j = 0; j < matrix[0].length; j++){
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println();
    }
    
    public static void main(String[] args){
        transposeMatrix tm = new transposeMatrix();
        
        // Test 1: Square matrix (3x3)
        System.out.println("Test 1: Square Matrix (3x3)");
        int[][] squareMatrix = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        
        System.out.println("Original matrix:");
        tm.printMatrix(squareMatrix);
        
        tm.getTranspose(squareMatrix);
        System.out.println("After in-place transpose:");
        tm.printMatrix(squareMatrix);
        
        // Test 2: Non-square matrix (2x3)
        System.out.println("Test 2: Non-square Matrix (2x3)");
        int[][] nonSquareMatrix = {
            {1, 2, 3},
            {4, 5, 6}
        };
        
        System.out.println("Original matrix:");
        tm.printMatrix(nonSquareMatrix);
        
        int[][] transposed = tm.getTransposeNew(nonSquareMatrix);
        System.out.println("Transposed matrix (new matrix):");
        tm.printMatrix(transposed);
        
        // Test 3: Single row matrix
        System.out.println("Test 3: Single Row Matrix (1x4)");
        int[][] singleRow = {{1, 2, 3, 4}};
        
        System.out.println("Original matrix:");
        tm.printMatrix(singleRow);
        
        int[][] transposedSingleRow = tm.getTransposeNew(singleRow);
        System.out.println("Transposed matrix:");
        tm.printMatrix(transposedSingleRow);
    }
}