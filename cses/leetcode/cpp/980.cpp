#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int rows, cols, res = 0, valid_squares_count = 0;
    bool isValid(int x, int rows)
    {
        return (0 <= x and x < rows);
    }
    void dfs(vector<vector<int>> &grid, int count, int x, int y)
    {
        if (grid[x][y] == -1 || !isValid(x, rows) || !isValid(y, cols))
            return;
        else
        {
            count++;
            if (grid[x][y] == 2)
            {
                if (count == valid_squares_count)
                    res++;
                cout << count << endl;
                return;
            }
            grid[x][y] = -1;
            dfs(grid, count, x + 1, y);
            dfs(grid, count, x, y + 1);
            dfs(grid, count, x - 1, y);
            dfs(grid, count, x, y - 1);
            grid[x][y] = 0; // backtracking step
        }
    }
    int uniquePathsIII(vector<vector<int>> &grid)
    {
        pair<int, int> start, finish;
        rows = grid.size();
        cols = grid[0].size();
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j] == 1)
                    start = {i, j};
                if (grid[i][j] != -1)
                    valid_squares_count++;
            }
        }
        int count = 0;
        dfs(grid, count, start.first, start.second);
        return res;
    }
};
int main()
{
    vector<vector<int>> grid = {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 2, -1}};
    Solution s;
    cout << s.uniquePathsIII(grid) << endl;
    return 0;
}