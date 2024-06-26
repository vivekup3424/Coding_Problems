#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// MAX_N * MAX_X
ll MAX_SUM = 2e5 * 1e9;

/**
 * true if the given `arr` can be divided into `k` subarrays where the sum of
 * each subarray is at most `max_sum`
 */
bool is_possible(const vector<ll> &arr, const int k, ll max_sum)
{
    // # of subarrays needed if sum of each subarray is at most max_sum
    int subarr_count = 0;
    // sum of the current subarray
    ll cur_sum = 0;

    for (const int &x : arr)
    {
        if (x > max_sum)
        {
            return false;
        }

        if (cur_sum + x > max_sum)
        {
            subarr_count++;
            cur_sum = 0;
        }
        cur_sum += x;
    }
    if (cur_sum > 0)
    {
        subarr_count++;
    }

    return subarr_count <= k;
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<ll> arr(n);
    for (ll &i : arr)
    {
        cin >> i;
    }

    ll l = 1, r = MAX_SUM;
    while (l < r)
    {
        ll mid = (l + r) / 2;
        if (is_possible(arr, k, mid))
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << l << '\n';
}