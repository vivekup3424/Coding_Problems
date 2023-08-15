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
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        integer n;
        cin >> n;
        int product = 1;
        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            product = (product * x) % 10;
        }
        if (product == 2 || product == 5 || product == 3)
            cout << "Yes\n";
        else
            cout << "no\n";
    }
    return 0;
}