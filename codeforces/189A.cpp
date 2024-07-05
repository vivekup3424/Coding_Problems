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
int solveBFS(int n, int a, int b, int c)
{
    queue<pair<int, int>> q; //{index. count}
    q.push({0, 0});
    int maxi = 0;
    while (!q.empty())
    {
        auto p = q.front();
        if (p.first == n)
        {
            maxi = max(maxi, p.second);
        }
        q.pop();
        if (p.first > n)
            continue;
        q.push({p.first + a, p.second + 1});
        q.push({p.first + b, p.second + 1});
        q.push({p.first + c, p.second + 1});
    }
    return maxi;
}
int solveMemoized(vector<int> &memo, int n, int a, int b, int c)
{
    if (memo[n] != -1)
        return memo[n];
    if (n == 0)
        return memo[n] = 0;
    if (n < 0)
        return memo[n] = INT_MIN;
    int x = solveMemoized(memo, n - a, a, b, c);
    int y = solveMemoized(memo, n - b, a, b, c);
    int z = solveMemoized(memo, n - c, a, b, c);
    return memo[n] = 1 + max(x, max(y, z));
}
// solve the problem using bottom up approach
int solveBottomUp(int n, int a, int b, int c)
{
    vector<int> dp(n + 1, INT_MIN);
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i - a >= 0)
            dp[i] = max(dp[i], 1 + dp[i - a]);
        if (i - b >= 0)
            dp[i] = max(dp[i], 1 + dp[i - b]);
        if (i - c >= 0)
            dp[i] = max(dp[i], 1 + dp[i - c]);
    }
    return dp[n];
}
int main()
{
    fast_io();
    int T = 1;
    while (T--)
    {
        int n, a, b, c;
        cin >> n >> a >> b >> c;
        vector<int> memo(n + 1, -1); // memoization
        cout << solveMemoized(memo, n, a, b, c) << "\n";
    }
}