#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
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
// let me write the recursive code first
// draw the decision tree, you will get
// the intuition from there
int total_ways(vll coins, int sum)
{
    if (sum == 0)
        return 1;
    else
    {
        ll total = 0;
        for (int i = 0; i < coins.size(); i++)
        {
            if (coins[i] <= sum)
            {
                total += total_ways(coins, sum - coins[i]);
            }
        }
        return total;
    }
}
// now I write the memoized code
// since this is a difficult question for me,
// I have to do this long process
ll total_ways_memo(vll coins, vll memo, ll sum)
{
    if (memo[sum] != -1)
        return memo[sum];
    else if (sum == 0)
        return memo[sum] = 1;
    else
    {
        ll total = 0;
        for (int i = 0; i < coins.size(); i++)
        {
            if (coins[i] <= sum)
            {
                total = (total + total_ways(coins, sum - coins[i])) % MOD;
            }
        }
        return memo[sum] = total;
    }
}
// well let's try the dp way
int main()
{
    ll n, x;
    cin >> n >> x;
    vll coins(n);
    inputVector(coins, n);
    sort(coins.begin(), coins.end());
    vll dp(x + 1, 0);
    dp[0] = 1;
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 0; j < x + 1; j++)
        {
            if (coins[i - 1] <= j)
            {
                dp[j] = (dp[j] + dp[j - coins[i - 1]]) % MOD;
            }
        }
    }
    cout << dp[x] << endl;
}
