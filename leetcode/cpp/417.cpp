#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        int n = heights.size(), m = heights[0].size();
        int maxDownRow[n][m];
        int maxUpRow[n][m];
        int maxLeftCol[n][m];
        int maxDownRow[n][m];
        for (int i = 0; i < n + 1; i++)
        {
            for (int j = 0; j < m + 1; j++)
            {
                if (i == 0 || j == 0)
                {
                    maxDownRow[i][j] = 0;
                }
            }
        }
    }
};