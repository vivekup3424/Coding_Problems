
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> v(m);
    for (int i = 0; i < m; i++)
    {
        cin >> v[i];
    }
    int min_diff = INT_MAX;
    sort(v.begin(), v.end());
    for (int i = 0; i <= m - n; i++)
    {
        min_diff = min(min_diff, v[i + n - 1] - v[i]);
    }
    cout << min_diff << endl;
}