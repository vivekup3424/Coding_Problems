#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long n;
        cin >> n;
        if (n % 4 != 0 && n % 6 != 0)
        {
            cout << -1 << endl;
        }
        int mini = n / 6;
        int maxi = n / 4;
        cout << mini << " " << maxi << endl;
    }
}