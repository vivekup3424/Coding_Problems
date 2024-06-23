#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
/**
 * Note that if a stripe is painted last, then the entire stripe appears in the
 * final picture (because no other stripe is covering it)
 *
 * Since rows are only painted red and columns are only painted blue, we can
 * just check if any row contains 8 Rs. If there is such a row, then red was
 * painted last; otherwise, blue was painted last.
 */
bool isRed(vector<vector<char>> &matrix)
{
    for (auto v : matrix)
    {
        if (v[0] == 'R' and v[1] == 'R' and v[2] == 'R' and v[3] == 'R' and v[4] == 'R' and v[5] == 'R' and v[6] == 'R' and v[7] == 'R')
        {
            return true;
        }
    }
    return false;
}
int main()
{
    fast_io();
    int T;
    cin >> T;
    while (T--)
    {
        vector<vector<char>> matrix(8, vector<char>(8));
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cin >> matrix[i][j];
            }
        }
        if (isRed(matrix))
        {
            cout << 'R' << endl;
        }
        else
        {
            cout << 'B' << endl;
        }
    }
    return 0;
}