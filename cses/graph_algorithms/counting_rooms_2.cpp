// I am going to recode this

#include <bits/stdc++.h>
using namespace std;
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
const int N = 1e3 + 10;
bool visited[N][N];
void dfs(int i, int j, vector<vector<char>> &matrix)
{
    int n = matrix.size(); // nxm
    int m = matrix[0].size();
    if (i <= 0 or j <= 0 or i >= n or j >= m or matrix[i][j] == '#')
        return;
    visited[i][j] = true;
    dfs(i, j + 1, matrix);
    dfs(i, j - 1, matrix);
    dfs(i + 1, j, matrix);
    dfs(i - 1, j, matrix);
}
int main()
{
    fast_io();
    int n, m;
    cin >> n >> m;
    vector<vector<char>> matrix;
    for (int i = 0; i < n; i++)
    {
        vector<char> row;
        for (auto j = 0; j < m; j++)
        {
            char c;
            cin >> c;
            row.push_back(c);
        }
        matrix.push_back(row);
    }
    int counter = 0;
    for (auto i = 0; i < n; i++)
    {
        for (auto j = 0; j < m; j++)
        {
            if (matrix[i][j] == '.' and !visited[i][j])
            {
                dfs(i, j, matrix);
                counter++;
            }
        }
    }
    cout << counter << "\n";
}