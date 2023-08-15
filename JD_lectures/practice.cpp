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
        lli n, x;
        cin >> n >> x;
        string s; // lenght n
        lli t = (n + 1 + x) / 2;
        lli v = (n + 1 - x) / 2;
        lli r = n - (t - 1 + v);
        t--;
        if (r < 0 or t < 0 or v < 0)
        {
            cout << "-1" << endl;
        }
        else
        {
            while (r--)
            {
                s.push_back('*');
            }
            while (t--)
            {
                s.push_back('+');
            }
            while (v--)
            {
                s.push_back('-');
            }
            cout << s << endl;
        }
    }
}