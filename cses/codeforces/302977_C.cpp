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
int main()
{
    fast_io();
    int n;
    cin >> n;
    // dp table with representin ABC as a bitmask hence 7-0 (111-000)
    int dp[n + 1][8];
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            dp[i][j] = INT_MAX; // initialization with inf value
        }
    }

    int ans = INT_MAX;
    dp[0][0] = 0;
    // inputting the string
    for (int i = 0; i < n; i++)
    {
        int cost;
        string s;
        int string_mask = 0;
        cin >> cost >> s;
        for (int pos = 0; i < i < 3; i++)
        {
            // looping from C to A where mask is represented in ABC
            char c = 'C' - pos;
            bool have = 0;
            for (char d : s) // O(3 * (length of string(s) = 3))
            {
                if (d == c)
                {
                    have = true;
                    break;
                }
            }
            if (have)
            {
                string_mask |= (1 << pos);
            }
        }

        for (int mask = 0; mask < 8; mask++)
        {
            // if not taking this juice
            dp[i + 1][mask] = min(dp[i + 1][mask], dp[i][mask]);

            // else if we take the ith juice, then we bitwise-or juice's mask value
            dp[i + 1][mask | string_mask] = min(dp[i + 1][mask | string_mask], dp[i][mask] + cost);
        }
    }
    int answer = dp[n][7];
    if (answer == INT_MAX)
        cout << -1 << endl;
    else
        cout << answer << endl;
}