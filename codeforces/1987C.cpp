#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc, char const *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        vector<long long> v(n);
        for (int i = 0; i < n; i++)
        {
            cin >> v[i];
        }
        ll sum = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            if (i == n - 1)
            {
                sum = v[i];
            }
            else
            {
                sum = max(sum + 1, v[i]);
            }
        }
        cout << "Sum = " << sum << endl;
    }
    return 0;
}
