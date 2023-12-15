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
    fast_io();
    int T;
    cin >> T;
    while (T--)
    {
        int a;
        cin >> a;
        vector<int> v;
        int power = 1;
        while (a > 0)
        {
            if (a % 10 > 0)
            {
                v.push_back((a % 10) * power);
            }
            a /= 10;
            power *= 10;
        }
        cout << v.size() << endl;
        for (auto n : v)
        {
            cout << n << " ";
        }
        cout << endl;
    }
}