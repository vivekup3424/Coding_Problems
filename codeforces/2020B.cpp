#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long k, l = 1, r = 2e18;
        cin >> k;
        while (r - l > 1)
        {
            long long mid = (l + r) >> 1;
            long long n = mid - int(sqrtl(mid));
            if (n >= k)
                r = mid;
            else
                l = mid;
        }
        cout << r << "\n";
    }
    return 0;
}