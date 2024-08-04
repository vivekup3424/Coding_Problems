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
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;

        vector<int> a(n);
        inputVector(a, n);
        // Find the minimum offset modulo k
        int min_mod = a[0] % k;
        for (int i = 1; i < n; i++)
        {
            min_mod = min(min_mod, a[i] % k);
        }

        // Calculate the maximum offset required to align all rooms
        int max_offset = 0;
        for (int i = 0; i < n; i++)
        {
            int offset = (a[i] % k - min_mod + k) % k;
            max_offset = max(max_offset, offset);
        }

        // The earliest time all lights are on is when the maximum offset is reached
        cout << max_offset + min_mod << endl;
    }

    return 0;
}