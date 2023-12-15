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
    int n, m; // n - num of tickets, m - num of customers
    cin >> n >> m;
    vector<int> price(n);
    vector<int> maximum_price(m);
    for (int i = 0; i < n; i++)
    {
        cin >> price[i];
    }
    for (int i = 0; i < m; i++)
    {
        cin >> maximum_price[i];
    }
    sort(price.begin(), price.end());
    sort(maximum_price.begin(), maximum_price.end());
    vector<int> result(m);
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (maximum_price[j] >= price[i])
        {
            result.push_back(price[i]);
            i++;
            j++;
        }
        else
            i++;
    }
    while (j < m)
    {
        result.push_back(-1);
    }
}