#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
    freopen("blist.in", "r", stdin);
    freopen("blist.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> v(10004, 0);
    while (n--)
    {
        int s, t, b;
        cin >> s >> t >> b;
        v[s] += b;
        v[t + 1] += -b;
    }
    int maxi = 0;
    for (int i = 1; i < v.size(); i++)
    {
        v[i] += v[i - 1];
        maxi = max(maxi, v[i]);
    }
    cout << maxi << endl;
    return 0;
}
