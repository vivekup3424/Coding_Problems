#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
void printVector(vector<int> t)
{
    for (auto a : t)
    {
        cout << a << " ";
    }
    cout << endl;
}
int main()
{
    fast_io();
    ll T;
    cin >> T;
    while (T--)
    {
        ll n, k, s;
        cin >> n >> k >> s;
        vector<ll> t(n);
        for (int i = 0; i < n; i++)
        {
            cin >> t[i];
        }
        sort(t.begin(), t.end());
    }
}