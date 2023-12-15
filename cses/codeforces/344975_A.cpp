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
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        lli ans = INT_MAX;
        while (n--)
        {
            lli temp;
            cin >> temp;
            ans = ans & temp;
        }
        cout << ans << endl;
    }
}