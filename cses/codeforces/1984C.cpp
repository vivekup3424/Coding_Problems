#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    for (; t > 0; t--)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        int sum = 0, mini = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
            sum += a[i];
            mini = min(mini, sum);
        }
        cout << sum - 2 * mini << endl;
    }
}