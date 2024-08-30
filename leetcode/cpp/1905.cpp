#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // 1 == land
    // 0 == water
    // 2 == visited land
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    bool isValid(int x, int y, vector<vector<int>> &grid)
    {
        if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size() || grid[x][y] != 1)
        {
            return false;
        }
        return true;
    }
    int countSubIslands(vector<vector<int>> &grid1, vector<vector<int>> &grid2)
    {
        int n = grid2.size();
        int m = grid2[0].size();
        int visited[n][m];
        memset(visited, 0, n * m);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid2[i][j] == 1 and visited[i][j] == 0)
                {
                    queue <
                }
            }
        }
    }
};