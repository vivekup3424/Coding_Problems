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
        ll n, l, r;
        cin >> n >> l >> r;
        vll v(n);
        inputVector(v, n);
        vll pref(n);
        ll count = 0;
        for (int i = 0; i < n; i++)
        {
            if (v[i] >= l and v[i] <= r)
            {
                count++;
                pref[i] = 0;
            }
            else
            {
                if (i == 0)
                {
                    pref[i] = v[i];
                }
                else
                {
                    pref[i] = v[i] + pref[i - 1];
                }
                // condition check
                if (pref[i] > r)
                {
                    pref[i] = 0;
                }
                else if (pref[i] >= l and pref[i] <= r)
                {
                    pref[i] = 0;
                    count++;
                }
            }
        }
        cout << count << endl;
    }
}