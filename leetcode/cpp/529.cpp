#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
class Solution
{
public:
    void dfs(vector<vector<char>> &board, int rows, int cols, int x, int y)
    {
        if (x < 0 || y < 0 || x >= rows || y >= cols || board[x][y] == 'B' || board[x][y] == 'X')
        {
            // if the cell is out of bounds or already visited
            return;
        }
        else if (board[x][y] == 'M')
        {
            // if I have stepped on a mine, press X (explode, ur dead)
            board[x][y] = 'X';
        }
        else
        {
            // I am currently at unrevealed blank tile

            // check if I have any mines in the vicinity of the current cell
            int count = 0; // number of mine
            for (auto dir : directions)
            {
                if (x + dir.first >= 0 && x + dir.first < rows && y + dir.second >= 0 && y + dir.second < cols &&
                    (board[x + dir.first][y + dir.second] == 'M' ||
                     board[x + dir.first][y + dir.second] == 'B'))
                {
                    count++;
                }
            }
            if (count > 0)
            {
                board[x][y] = (char)(count + '0');
            }
            else
            {
                // no mines in the vicinity and current cell is blank
                // mark it B
                board[x][y] = 'B';
                // do dfs on its neightborhood
                for (auto dir : directions)
                {
                    dfs(board, rows, cols, x + dir.first, y + dir.second);
                }
            }
        }
    }
    vector<vector<char>> updateBoard(vector<vector<char>> &board, vector<int> &click)
    {
        // M = mine
        // E,B = space (unrevealed/revelead) respectively
        int rows = board.size();
        int cols = board[0].size();
        int x = click[0], y = click[1];
        if (board[x][y] == 'M')
        {
            board[x][y] = 'X';
        }
        else
        {
            dfs(board, rows, cols, x, y);
        }

        return board;
    }
};