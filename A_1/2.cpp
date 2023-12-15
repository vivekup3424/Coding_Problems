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
    int n;
    cin >> n;
    int temp = n - 1;
    int t;
    vector<int> v;
    while (temp--)
    {
        cin >> t;
        v.push_back(t);
    }
    int r = 0;
    for (int i = 1; i <= n; i++)
    {
        r ^= i;
    }
    for (int i = 0; i < v.size(); i++)
    {
        r ^= v[i];
    }
    cout << r << "\n";
}