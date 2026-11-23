/*
 * 1853A. Desorting
 * https://codeforces.com/problemset/problem/1853/A
 *
 * (Statement, Input/Output, examples and limits not filled in - paste the
 * problem text to complete this header.)
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fast_io();
    ll T;
    cin >> T;
    while (T--)
    {
        ll n;
        cin>>n;
        vector<int> v(n);
        int ans = INT_MAX;
        bool unsorted = false;
        for (ll i = 0; i < n; i++)
        {
            cin>>v[i];
            if(i > 0){
                if (v[i] < v[i-1])
                    unsorted = true;
                ans = min(ans,1 + (v[i]-v[i-1])/2);
            }
        }
        if (unsorted)
            ans = 0;
        cout<<ans<<"\n";
    }
}
