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
llu sum(llu k)
{
    return (k * (k + 1)) / 2;
}
int main()
{
    llu n, k;
    cin >> n >> k;
    if (((sum(k - 1) + 1)) < n)
    {
        cout << -1 << endl;
        return 0;
    }
    int low = 0, high = k - 1, ans = 0;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (sum(k - 1) - sum(mid) == n)
        {
            cout << mid << endl;
            return 0;
        }
        else if (sum(k - 1) - sum(mid) > n)
        {
            low = mid + 1;
            ans = mid;
        }
        else
        {
            high = mid - 1;
        }
    }
    cout << k - 1 - high << endl;
    return 0;
}