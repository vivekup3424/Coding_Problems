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
class Solution
{
public:
    bool winnerSquareGame(int n)
    {
        vll squares;
        for (int i = 1; i <= sqrt(n); i++)
        {
            squares.push_back(i * i);
        }
        vector<bool> dp(n + 1);
        dp[0] = false;
        for (int i = 1; i <= n; i++)
        {
            for (auto j : squares)
            {
                if (i - j < 0)
                {
                    break;
                }
                dp[i] = dp[i] || !dp[i - j];
            }
        }
        return dp[n];
    }
};
int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n;
        cin >> n;
        cout << Solution().winnerSquareGame(n) << endl;
    }
}
