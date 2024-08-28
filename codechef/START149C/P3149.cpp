#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<long long> vll;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

ll maxSubarraySum(vll &v)
{
    ll max_sum = LLONG_MIN, current_sum = 0;
    for (ll x : v)
    {
        current_sum += x;
        if (current_sum > max_sum)
            max_sum = current_sum;
        if (current_sum < 0)
            current_sum = 0;
    }
    return max_sum;
}

int main()
{
    fast_io();
    ll T;
    cin >> T;
    while (T--)
    {
        ll n;
        cin >> n;
        vll v(n);
        for (int i = 0; i < n; i++)
        {
            cin >> v[i];
        }

        ll original_max = maxSubarraySum(v);
        int operations_needed = 0;

        // Count the number of negative numbers that we might need to set to zero
        for (int i = 0; i < n; i++)
        {
            if (v[i] < 0)
            {
                ll temp = v[i];
                v[i] = 0; // temporarily set to zero
                if (maxSubarraySum(v) > original_max)
                {
                    operations_needed++;
                    original_max = maxSubarraySum(v);
                }
                v[i] = temp; // restore the value
            }
        }

        cout << operations_needed << endl;
    }

    return 0;
}
