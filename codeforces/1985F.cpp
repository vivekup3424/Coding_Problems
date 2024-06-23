#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
typedef std::vector<vector<long long>> vvll;
const int MOD = 1e9 + 7;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cout.tie(NULL);
}

// Template function to input elements to a vector
template <typename T>
void inputVector(vector<T> &v, int n)
{
    v.resize(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> v[i];
    }
}

// Template function to output elements of a vector
template <typename T>
void outputVector(const vector<T> &v, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << "\n";
}

int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll h, n;
        cin >> h >> n;
        vll a(n);
        inputVector(a, n);
        vll b(n);
        inputVector(b, n);
        ll l = 0, r = INT64_MAX;
        ll ans = 0;
        while (l <= r)
        {
            ll m = (l + r) >> 1;
            ll s = 0;
            for (int i = 0; i < n; i++)
            {
                ll num = m / b[i];
                s += (num + 1) * a[i];
            }
            if (s >= h || s < 0)
            {
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }
        cout << ans + 1 << endl;
    }
}