#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// function to calculate minimum area of rectangle, enclosing
// all the ones in a submatrix defined by corners st_i,en_i,st_j,en_j
int minimumArea(vector<vector<int>> &grid, int st_i, int en_i, int st_j, int en_j)
{
    int i, j, start_row = 1e9, end_row = -1, start_col = 1e9, end_col = -1, found = 0;
    for (i = st_i; i <= en_i; i++)
        for (j = st_j; j <= en_j; j++)
        {
            if (grid[i][j])
            {
                start_row = min(start_row, i);
                end_row = max(end_row, i);
                start_col = min(start_col, j);
                end_col = max(end_col, j);
                found = 1;
            }
        }
    return found ? ((end_row - start_row + 1) * (end_col - start_col + 1)) : 0;
}