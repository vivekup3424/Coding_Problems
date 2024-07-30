#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> v(n);
        for (auto &x : v)
            cin >> x;
        int maxi = max(v[0], v[n - 1]);
        for (int i = 0; i < n - 2; i++)
        {
            maxi = max(maxi, v[i]);
        }
        for (int i = n - 1; i > 1; i--)
        {
            maxi = max(maxi, v[i]);
        }
        cout << maxi << endl;
    }
    return 0;
}
