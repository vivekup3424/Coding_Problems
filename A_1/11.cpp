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
        llu a, b;
        cin >> a >> b;
        if ((a + b) % 3 != 0)
            cout << "NO\n";
        else if (min(a, b) >= (a + b) / 3)
        {
            cout << "YES\n";
        }
        else
            cout << "NO\n";
    }
    return 0;
}