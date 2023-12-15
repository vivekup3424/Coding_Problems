#include <bits/stdc++.h>
using namespace std;

int solve(vector<int> arr, int n, int m) // n = starting index,m = ending index
{
    int t[n + 1][m + 1];
    // for Ai (arr[i-1] x arr[i])
    memset(t, 0, (n + 1) * (m + 1));
    for (int l = 2; l < n; l++)
        for (int i = 1, j = i + l - 1; i < n - l + 1; i++, j = i + l - 1)
        {
            t[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++)
            {
                int q = t[i][k] + t[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                if (q < t[i][j])
                {
                    t[i][j] = q;
                }
            }
        }
    cout << t[n][m] << "\n";
    return t[n][m];
}

int main()
{
    vector<int> arr = {10, 20, 30};
    solve(arr, 1, 2);
}