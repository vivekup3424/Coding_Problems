class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int x = matrix.size();
        int y = matrix[0].size();
        int startRow = 0, endRow = x - 1;

        // Perform binary search on rows
        while (startRow <= endRow) {
            int middleRow = startRow + (endRow - startRow) / 2;
            int value = matrix[middleRow][0];

            if (value == target) {
                return true;
            } else if (value < target) {
                startRow = middleRow + 1;
            } else {
                endRow = middleRow - 1;
            }
        }

        if (endRow < 0) {
            return false;
        }

        int row = endRow;
        int startCol = 0, endCol = y - 1;

        // Perform binary search on columns
        while (startCol <= endCol) {
            int middleCol = startCol + (endCol - startCol) / 2;
            int value = matrix[row][middleCol];

            if (value == target) {
                return true;
            } else if (value < target) {
                startCol = middleCol + 1;
            } else {
                endCol = middleCol - 1;
            }
        }

        return false;
    }
};
// I am going to use binary search
