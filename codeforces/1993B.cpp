#include <bits/stdc++.h>
using namespace std;

// Type definitions
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
typedef std::vector<vector<long long>> vvll;
const long long MOD = LLONG_MAX;
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
    std::cin >> T;
    while (T--)
    {
        // sum of distint parity is odd
        // count the number of even numbers
        int n;
        cin >> n;
        vll v(n);
        inputVector(v, n);
        int num_evens = 0, num_odds = 0;
        ll max_odd = INT_MIN;
        for (auto i : v)
        {
            if (i % 2 == 0)
            {
                num_evens++;
            }
            else
            {
                num_odds++;
                max_odd = max(max_odd, i);
            }
        }
        if (num_odds == 0 || num_evens == 0)
        {
            cout << 0 << endl;
        }
        else
        {
            sort(v.begin(), v.end());
            // converting everyone to odd
            int count = 0;
            for (auto i : v)
            {
                // cout << "max_odd = " << max_odd << ", i = " << i << endl;
                if (i % 2 == 0)
                {
                    if (i < max_odd)
                    {
                        count++;
                    }
                    else
                    {
                        count += 2;
                    }
                    max_odd = (max_odd + i) % MOD;
                }
            }
            cout << count << endl;
        }
    }

    return 0;
}