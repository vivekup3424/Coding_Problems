
#include <bits/stdc++.h>
using namespace std;
class Solution1
{
    // brute force approach, mark all the required rows and cols
    void markRow(vector<vector<int>> matrix, int row_index)
    {
        int cols = matrix[0].size();
        for (int j = 0; j < cols; j++)
        {
            if (matrix[row_index][j] == 1)
            {
                matrix[row_index][j] = -1;
            }
        }
    }
    void markCol(vector<vector<int>> matrix, int col_index)
    {
        int rows = matrix.size();
        for (int i = 0; i < rows; i++)
        {
            if (matrix[i][col_index] == 1)
            {
                matrix[i][col_index] = -1;
            }
        }
    }

public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        int n = matrix.size(), m = matrix[0].size();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                markRow(matrix, i);
                markCol(matrix, j);
            }
        }

        // now making all -1 marked elements to 0 in a single-pass
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (matrix[i][j] == -1)
                {
                    matrix[i][j] = 0;
                }
            }
        }
        return;
        // Time complexity = m*n(m+n) + (m*n)
    }
};
int main()
{
}