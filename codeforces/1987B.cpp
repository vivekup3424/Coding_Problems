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
        ll n;
        cin >> n;
        vll v(n);
        inputVector(v, n);
        ll countCoins = 0;
        vll greaterElement(n, 0);
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                greaterElement[i] = v[i];
            }
            else
            {
                greaterElement[i] = max(v[i], greaterElement[i - 1]);
            }
        }
        vll diff;
        for (int i = 0; i < n; i++)
        {
            auto d = greaterElement[i] - v[i];
            if (d > 0)
            {
                diff.push_back(d);
            }
        }
        sort(diff.begin(), diff.end());
        int m = diff.size();
        ll sum = 0;
        ll start = 0;
        for (int i = 0; i < m; i++)
        {
            ll d = diff[i] - start;
            if (d > 0)
            {
                sum += d * (m - i + 1);
                start += d;
            }
        }
        cout << sum << endl;
    }
}