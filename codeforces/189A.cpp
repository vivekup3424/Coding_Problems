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
int solve(int n, int a, int b, int c)
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
int main()
{
    fast_io();
    int T = 1;
    while (T--)
    {
        int n, a, b, c;
        cin >> n >> a >> b >> c;
        cout << solve(n, a, b, c) << "\n";
    }
}