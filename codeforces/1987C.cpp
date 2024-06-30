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
bool containsNonZero(vll v)
{
    for (auto i : v)
    {
        if (i != 0)
        {
            return true;
        }
    }
    return false;
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
        // try simulating the process
        ll count = 0;
        while (containsNonZero(v))
        {
            for (int i = 0; i < n; i++)
            {
                if (i < n - 1 and v[i] > v[i + 1])
                {
                    v[i] = max((ll)0, v[i] - 1);
                }
                else if (i == n - 1)
                {
                    v[i] = max((ll)0, v[i] - 1);
                }
            }
            count++;
            cout << "Count = " << count << endl;
            outputVector(v, n);
        }
    }
}