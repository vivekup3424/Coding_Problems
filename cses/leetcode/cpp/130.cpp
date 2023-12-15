
#include <bits/stdc++.h>
using namespace std;
// Method 1:- Following my thought process.
class Solution
{
public:
    void dfs(int x, int y, int rows, int cols, vector<vector<char>> &grid, char O, char X)
    {
        if (x < 0 or y < 0 or x >= rows or y >= cols or grid[x][y] != O)
        {
            return;
        }
        grid[x][y] = X;
        dfs(x - 1, y, rows, cols, grid, O, X);
        dfs(x, y - 1, rows, cols, grid, O, X);
        dfs(x + 1, y, rows, cols, grid, O, X);
        dfs(x, y + 1, rows, cols, grid, O, X);
    }
    void solve(vector<vector<char>> &b)
    {
        int r = b.size(), c = b[0].size();
        int count = 0;
        char V = 'V'; // visited
        // run dfs on border
        // top
        for (int j = 0; j < c; j++)
        {
            if (b[0][j] == '0')
            {
                dfs(0, j, r, c, b, '0', V);
            }
        }
        // right
        for (int i = 0; i < r; i++)
        {
            if (b[i][c - 1] == '0')
            {
                dfs(i, c - 1, r, c, b, '0', V);
            }
        }
        // bottom
        for (int j = 0; j < c; j++)
        {
            if (b[r - 1][j] == '0')
            {
                dfs(r - 1, j, r, c, b, '0', V);
            }
        }
        // left
        for (int i = 0; i < r; i++)
        {
            if (b[i][0] == '0')
            {
                dfs(i, 0, r, c, b, '0', V);
            }
        }
        // after marking all the outside territory
        // mark the inside teritory
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (b[i][j] == 'O')
                {
                    b[i][j] = 'X';
                }
            }
        }
        // undo marking the outside teritorry
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (b[i][j] == V)
                {
                    b[i][j] = 'O';
                }
            }
        }
    }
};
// the above code is so long and efficient, I need to have a better code for
// this program.
int main()
{
    vector<vector<char>> board = {
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'}};

    Solution sol;
    sol.solve(board);

    // Print the modified board
    for (const auto &row : board)
    {
        for (char cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }

    return 0;
}