#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<vector<ll>> Matrix;

bool isPeak(const Matrix &mat, int i, int j, int n, int m)
{
    int val = mat[i][j];
    if (i > 0 && mat[i - 1][j] >= val)
        return false; // top neighbor
    if (i < n - 1 && mat[i + 1][j] >= val)
        return false; // bottom neighbor
    if (j > 0 && mat[i][j - 1] >= val)
        return false; // left neighbor
    if (j < m - 1 && mat[i][j + 1] >= val)
        return false; // right neighbor
    return true;
}
ll maximumSmallestNeighbor(const Matrix &mat, int i, int j, int n, int m)
{
    ll val = mat[i][j];
    ll maxNeighbor = -1; // Start with an invalid value

    // Check top neighbor
    if (i > 0 && mat[i - 1][j] < val)
    {
        maxNeighbor = max(maxNeighbor, mat[i - 1][j]);
    }
    // Check bottom neighbor
    if (i < n - 1 && mat[i + 1][j] < val)
    {
        maxNeighbor = max(maxNeighbor, mat[i + 1][j]);
    }
    // Check left neighbor
    if (j > 0 && mat[i][j - 1] < val)
    {
        maxNeighbor = max(maxNeighbor, mat[i][j - 1]);
    }
    // Check right neighbor
    if (j < m - 1 && mat[i][j + 1] < val)
    {
        maxNeighbor = max(maxNeighbor, mat[i][j + 1]);
    }

    return maxNeighbor;
}
void stabilizeMatrix(Matrix &mat, int n, int m)
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (isPeak(mat, i, j, n, m))
            {
                mat[i][j] = maximumSmallestNeighbor(mat, i, j, n, m);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        Matrix mat(n, vector<ll>(m));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> mat[i][j];
            }
        }

        stabilizeMatrix(mat, n, m);

        for (const auto &row : mat)
        {
            for (ll val : row)
            {
                cout << val << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}
