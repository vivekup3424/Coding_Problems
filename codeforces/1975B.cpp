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
        ll a = 0, b = 0;
        sort(v.begin(), v.end());
        a = v[0];
        // get b
        for (int i = 0; i < n; i++)
        {
            if (v[i] % a != 0)
            {
                b = v[i];
                break;
            }
        }
        if (b == 0)
        {
            cout << "YES\n";
        }
        else
        {
            bool isDivisible = true;
            for (int i = 0; i < n; i++)
            {
                if (v[i] % a != 0 && v[i] % b != 0)
                {
                    isDivisible = false;
                    break;
                }
            }
            cout << (isDivisible ? "YES" : "NO") << endl;
        }
    }
}