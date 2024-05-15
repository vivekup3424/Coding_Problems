#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
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
    int dfs(vector<vector<int>> &grid,
            vector<vector<bool>> &visited,
            vector<vector<int>> &manhattan,
            int i, int j,
            int &maxMahattan)
    {
        int n = grid.size();
        if (i < 0 or j < 0 or i >= n or j >= n or visited[i][j])
        {
            return INT_MAX;
        }
        visited[i][j] = true;
        maxMahattan = min(maxMahattan, manhattan[i][j]);
        if (i == n - 1 and j == n - 1)
        {
            return maxMahattan;
        }
        else
        {
            return min(
                {
                    dfs(grid, visited, manhattan, i - 1, j, maxMahattan),
                    dfs(grid, visited, manhattan, i + 1, j, maxMahattan),
                    dfs(grid, visited, manhattan, i, j - 1, maxMahattan),
                    dfs(grid, visited, manhattan, i, j + 1, maxMahattan),
                });
        }
    }
    int maximumSafenessFactor(vector<vector<int>> &grid)
    {
        int rows = grid.size(), cols = grid[0].size();
        vector<vector<int>> manhattan(
            rows,
            vector<int>(cols, INT_MAX));

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j] == 1)
                {
                    manhattan[i][j] = 0;
                    // up
                    while (i - 1 >= 0 and grid[i - 1][j] != 1)
                    {
                        manhattan[i - 1][j] = min(
                            manhattan[i - 1][j],
                            manhattan[i][j] + 1);
                    }
                    // down
                    while (i + 1 < rows and grid[i + 1][j] != 1)
                    {
                        manhattan[i + 1][j] = min(
                            manhattan[i + 1][j],
                            manhattan[i][j] + 1);
                    }
                    // left
                    while (j - 1 >= 0 and grid[i][j - 1] != 1)
                    {
                        manhattan[i][j - 1] = min(
                            manhattan[i][j - 1],
                            manhattan[i][j] + 1);
                    }
                    // right
                    while (j + 1 < cols and grid[i][j + 1] != 1)
                    {
                        manhattan[i][j + 1] = min(
                            manhattan[i][j + 1],
                            manhattan[i][j] + 1);
                    }
                }
            }
        }
        printMatrix(manhattan);
        vector<vector<bool>> visited(
            rows,
            vector<bool>(cols, false));
        int maxMahattan = INT_MAX;
        return dfs(grid, visited, manhattan, 0, 0, maxMahattan);
    }
};