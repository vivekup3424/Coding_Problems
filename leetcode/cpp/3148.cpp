#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxScore(vector<vector<int>> &grid)
    {
        int rows = grid.size(), cols = grid.size();
        vector<vector<int>> dp1(rows - 1, vector<int>(cols - 1, 0));
        vector<vector<int>> dp2(rows - 1, vector<int>(cols - 1, 0));
        vector<vector<int>> dp3(rows - 1, vector<int>(cols - 1, 0));
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (j - 1 >= 0)
                {
                    dp1[i][j] = grid[i][j] - grid[i][j - 1];
                }
                if (i - 1 >= 0)
                {
                    dp2[i][j] = grid[i][j] - grid[i - 1][j];
                }
            }
        }
    }
};