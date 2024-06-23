#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long int n;
        cin >> n;
        long long int ans = (n + 1) * n / 2 - 2;
        for (int i = 1; pow(2, i) <= n; i++)
            ans -= pow(2, i + 1);
        cout << ans << endl;
    }
    return 0;
}