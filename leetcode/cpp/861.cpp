#include <bits/stdc++.h>
using namespace std;
template <typename T>
void printMatrix(const vector<vector<T>> &matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
class Solution
{
public:
    int matrixScore(vector<vector<int>> &grid)
    {
        int rows = grid.size(), cols = grid[0].size();
        vector<vector<int>> temp = grid;
        for (int i = 0; i < rows; i++)
        {
            if (temp[i][0] == 0)
            {
                for (int j = 0; j < cols; j++)
                {
                    temp[i][j] = !temp[i][j];
                }
            }
        }
        for (int j = 0; j < cols; j++)
        {
            int count1 = 0, count0 = 0;
            for (int i = 0; i < rows; i++)
            {
                temp[i][j] == 1 ? count1++ : count0++;
            }
            if (count0 > count1)
            {
                // toggle the bits of the colums
                for (int i = 0; i < rows; i++)
                {
                    temp[i][j] = !temp[i][j];
                }
            }
        }
        cout << "resultant matrix" << endl;
        printMatrix(temp);
        int sum = 0;
        for (int i = 0; i < rows; i++)
        {
            int t = 0;
            for (int j = 0; j < cols; j++)
            {
                t = 2 * t + temp[i][j];
            }
            sum += t;
        }
        return sum;
    }
};