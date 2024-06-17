#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    int n;
    cin >> n;
    vector<pair<ll, ll>> vertices(n);
    for (int i = 0; i < n; i++)
    {
        cin >> vertices[i].first >> vertices[i].second;
    }
    ll sum = 0;
    for (int i = 0; i < n; i++)
    {
        int p1 = i;
        int p2 = (i + 1) % n;
        sum += ((vertices[p1].first * vertices[p2].second) -
                (vertices[p1].second * vertices[p2].first));
    }
    cout << abs(sum) << endl;
}