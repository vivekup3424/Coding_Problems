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
    lli n, k;
    cin >> n >> k;
    string s;
    cin >> s; // length(s) = n
    set<char> st;
    for (int i = 0; i < k; i++)
    {
        char c;
        cin >> c;
        st.insert(c);
    }

    lli dp[n + 1];
    lli l = 0; // length of current valid substring
    for (lli i = 0; i <= n; i++)
    {
        if (i == 0)
        {
            dp[i] = 0; // initlialization
        }
        else
        {
            if (st.count(s[i - 1]))
            {
                // characters belongs to the valid set
                l++;
            }
            else
            {
                // if characterdoes not belongs to the valid set
                l = 0;
            }
            dp[i] = dp[i - 1] + l;
        }
    }
    cout << dp[n] << endl;
}