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
ll logBase3(ll x)
{
    int sum = 0;
    while (x > 0)
    {
        sum++;
        x /= 3;
    }
    return sum;
}
int main(int argc, char const *argv[])
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll l, r;
        cin >> l >> r;
        vll v;
        ll maxi = -1;
        for (ll i = l; i <= r; i++)
        {
            if (i % 3 == 2 and maxi == -1)
            {
                maxi = i;
            }
            v.push_back(i);
        }
        if (maxi == -1)
        {
            maxi = v[0];
        }
        ll numCounts = 0;
        int count = logBase3(v[0]);
        for (auto i : v)
        {
            numCounts += count;
            if (i == maxi)
            {
                numCounts += count;
            }
            if (i % 3 == 0)
            {
                count++;
            }
        }
        cout << numCounts << endl;
    }

    return 0;
}