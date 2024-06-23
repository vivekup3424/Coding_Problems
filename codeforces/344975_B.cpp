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
const int MOD = 1e9 + 7;
int main()
{
    fast_io();
    int T;
    cin >> T;
    while (T--)
    {
        int n, k;
        cin >> n >> k;
        lli ans = 1;
        for (int i = 1; i <= k; i++)
        {
            ans = (ans * n) % MOD;
        }
        cout << ans << endl;
    }
}