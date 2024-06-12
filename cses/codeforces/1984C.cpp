#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
    ll t;
    cin >> t;
    for (; t > 0; t--)
    {
        ll n;
        cin >> n;
        vector<ll> a(n);
        ll sum = 0, mini = 0;
        for (ll i = 0; i < n; i++)
        {
            cin >> a[i];
            sum += a[i];
            mini = min(mini, sum);
        }
        cout << sum - 2 * mini << endl;
    }
}