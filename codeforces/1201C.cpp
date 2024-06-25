#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
typedef std::vector<vector<long long>> vvll;
const ll MOD = 1e9 + 7;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cout.tie(NULL);
}

// Template function to input elements to a vector
template <typename T>
void inputVector(vector<T> &v, ll n)
{
    v.resize(n);
    for (ll i = 0; i < n; i++)
    {
        std::cin >> v[i];
    }
}

// Template function to output elements of a vector
template <typename T>
void outputVector(const vector<T> &v, ll n)
{
    for (ll i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << "\n";
}
ll evalutateFunction(vector<long long> v, ll x)
{
    ll n = v.size();
    ll middle = (n + 1) / 2;
    ll sum = 0;
    for (ll i = middle; i < n; i++)
    {
        sum += max((long long)0, x - v[i]);
    }
    return sum;
}
int main()
{
    fast_io();
    ll n, k;
    cin >> n >> k;
    vll v(n);
    inputVector(v, n);
    sort(v.begin(), v.end());
    ll x = -1; // find the lower-bound of x, that satisfies the problem requirements
    ll l = v[(n + 1) / 2], r = v[(n + 1) / 2] + k;
    while (l <= r)
    {
        ll mid = l + (r - l) / 2;
        ll value = evalutateFunction(v, mid);
        if (value <= k)
        {
            x = mid;
            r = mid + 1;
        }
        else
        {
            l = mid - 1;
        }
    }
    cout << x << endl;
    return 0;
}
