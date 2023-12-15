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
    llu n, m, k;
    cin >> n >> m >> k;
    vector<int> desired;
    vector<int> available;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        desired.push_back(temp);
    }
    for (int i = 0; i < m; i++)
    {
        int temp;
        cin >> temp;
        available.push_back(temp);
    }
    // k - max allowed difference
    sort(desired.begin(), desired.end());
    sort(available.begin(), available.end());
    int count = 0, j = 0, i = 0;
    while (i < n and j < m)
    {
        if (abs(desired[i] - available[j]) <= k)
        {
            ++count;
            ++j;
            ++i;
        }
        else if ((desired[i] - available[j]) > k)
        {
            ++j;
        }
        else
        {
            ++i;
        }
    }
    cout << count << "\n";
    return 0;
}