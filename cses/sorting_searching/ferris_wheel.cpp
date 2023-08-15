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
    int n, x;
    cin >> n >> x;

    vector<int> v;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        v.push_back(temp);
    }
    int i = 0, j = n - 1, count = 0;
    sort(v.begin(), v.end());
    while (i <= j)
    {
        if ((v[i] + v[j]) <= x)
        {
            count++;
            i++;
            j--;
        }
        else if (v[j] <= x)
        {
            count++;
            j--;
        }
    }
    cout << count << "\n";
    return 0;
}