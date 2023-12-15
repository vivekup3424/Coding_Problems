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
        lli n;
        cin >> n;
        vector<lli> v(n);
        for (lli i = 0; i < n; i++)
        {
            cin >> v[i];
        }

        // count the number of elements in the array that have the MSB at ith place
        vector<lli> count(63, 0); // as I am using 64 bit integers
        for (lli i = 0; i < n; i++)
        {
            lli MSB = 63 - __builtin_clzll(v[i]); //__builtin_clzll() returns the number of leading zeroes in a 64 bit integer
            count[MSB]++;                         // increment the count of the number of elements that have the MSB at ith place
        }

        // now number of pairs that have the MSB at ith place is count[i]*(count[i]-1)/2
        // hence these pairs would have bitwise AND greater that their bitwise XOR

        lli ans = 0;
        for (lli i = 0; i < 63; i++)
        {
            ans += count[i] * (count[i] - 1) / 2;
        }
        cout << ans << endl;
    }
}