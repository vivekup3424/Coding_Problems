#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        vector<int> v(n);
        for (int i = 0; i < n; i++)
        {
            cin >> v[i];
        }
        sort(v.rbegin(), v.rend());
        int sum1 = 0, sum0 = 0;
        for (int i = 0; i < n; i++)
        {
            if (i % 2 == 0)
            {
                sum0 += v[i];
            }
            else
            {
                int diff = v[i - 1] - v[i];
                if (diff <= k)
                {
                    sum1 += v[i] + diff;
                    k -= diff;
                }
                else
                {
                    sum1 += v[i] + k;
                    k = 0;
                }
            }
        }
        // output sum1 and sum0
        // cout << sum1 << " " << sum0 << endl;
        // output diff
        cout << max(sum0 - sum1, 0) << endl;
    }
    return 0;
}
