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
// returns the index the lowest index of element >= currentElement
ll lowerBound(vll v, int x)
{
    ll val = -1;
    ll n = v.size();
    ll l = 0, r = n;
    while (l <= r)
    {
        ll mid = l + (r - l) / 2;
        if (v[mid] >= x)
        {
            r = mid - 1;
            val = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    // cout << "lowerBound index = " << val << endl;
    return val;
}
// returns the highest index of the element <= current_element
ll upperBound(vll v, int x)
{
    ll val = -1;
    ll n = v.size();
    ll l = 0, r = n;
    while (l <= r)
    {
        ll mid = l + (r - l) / 2;
        if (v[mid] <= x)
        {
            l = mid + 1;
            val = mid;
        }
        else
        {
            r = mid - 1;
        }
    }
    // cout << "upper Bound index = " << val << endl;
    return val;
}

int main()
{
    fast_io();
    ll n, q;
    cin >> n >> q;
    vll v(n);
    inputVector(v, n);
    sort(v.begin(), v.end());
    while (q--)
    {
        ll a, b;
        cin >> a >> b;
        if (lowerBound(v, a) == -1)
        {
            cout << 0;
        }
        else
        {
            ll l_a = max((ll)0, lowerBound(v, a));
            ll u_b = min(upperBound(v, b), (ll)n - 1);
            cout << u_b - l_a + 1 << endl;
        }
    }
}