#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
typedef std::vector<vector<long long>> vvll;
const int MOD = 1e9 + 7;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cout.tie(NULL);
}

// Template function to input elements to a vector
template <typename T>
void inputVector(vector<T> &v, int n)
{
    v.resize(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> v[i];
    }
}

// Template function to output elements of a vector
template <typename T>
void outputVector(const vector<T> &v, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << "\n";
}
void dfs(vector<vector<char>> grid, int n, int m, vector<vector<bool>> &visited, int i, int j, int component_size)
{
    if (i < 0 or j < 0 or i >= n or j >= m or visited[i][j] == true or grid[i][j] == '.')
    {
        return;
    }
    visited[i][j] = true;
    dfs(grid, n, m, visited, i, j + 1);
    dfs(grid, n, m, visited, i, j - 1);
    dfs(grid, n, m, visited, i + 1, j);
    dfs(grid, n, m, visited, i - 1, j);
    return;
}
int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n, m;
        cin >> n >> m;
        vector<vector<char>> mat(n, vector<char>(m, '.'));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> mat[i][j];
            }
        }
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (visited[i][j] == false)
                {
                    dfs(grid, n, m, visited, i, j)
                }
            }
        }
    }
}