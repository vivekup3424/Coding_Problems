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
    ll n, x;
    cin >> n >> x;
    vll a(n);
    inputVector(a, n);
    map<int, int> mp;
    bool isImpossible = true;
    for (int i = 0; i < n; i++)
    {
        int comp = x - a[i];
        if (mp.find(comp) != mp.end())
        {
            cout << mp[comp] + 1 << " " << i + 1 << endl;
            isImpossible = false;
            break;
        }
        else
        {
            mp[a[i]] = i;
        }
    }
    if (isImpossible)
    {
        cout << "IMPOSSIBLE" << endl;
    }
}
