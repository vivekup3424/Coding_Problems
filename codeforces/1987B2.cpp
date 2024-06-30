#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ll T;
    cin >> T;
    while (T--)
    {
        ll n;
        cin >> n;
        vector<ll> v(n);
        for (ll i = 0; i < n; ++i)
        {
            cin >> v[i];
        }

        ll countCoins = 0;

        for (ll i = 1; i < n; ++i)
        {
            if (v[i] < v[i - 1])
            {
                countCoins += (v[i - 1] - v[i]) * (n - i + 1);
                v[i] = v[i - 1];
            }
        }

        cout << countCoins << endl;
    }
    return 0;
}
