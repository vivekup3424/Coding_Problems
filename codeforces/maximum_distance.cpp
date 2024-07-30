#include <bits/stdc++.h>
using namespace std;

// Type definitions
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
typedef std::vector<vector<long long>> vvll;
const int MOD = 1e9 + 7;

// Fast I/O setup
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cout.tie(NULL);
}

// Template function to input elements into a vector
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

int main(int argc, char const *argv[])
{
    fast_io();
    ll T;
    T = 1;
    while (T--)
    {
        ll n;
        cin >> n;
        vector<pair<ll, ll>> v;
        for (int i = 0; i < n; i++)
        {
            pair<ll, ll> p;
            cin >> p.first >> p.second;
            v.push_back(p);
        }
        ll maxi = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                maxi = max((double)maxi, pow(v[i].first - v[j].first, 2) + pow(v[i].second - v[j].second, 2));
            }
        }
        cout << maxi << "\n";
    }

    return 0;
}