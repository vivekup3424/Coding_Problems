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
        vll a(n);
        inputVector(a, n);
        vll b(n);
        inputVector(b, n);
        ll m;
        cin >> m;
        vll d(m);
        inputVector(d, m);
        map<int, int> mp1, mp2;
        for (int i = 0; i < n; i++)
        {
            if (a[i] != b[i])
            {
                mp1[b[i]]++;
            }
        }
        for (auto num : d)
        {
            mp2[num]++;
        }
        vll deleteValues;
        bool doesntExist = false;
        for (auto it : mp2)
        {
            if (mp1.find(it.first) == mp1.end())
            {
                doesntExist = true;
                break;
            }
            mp1[it.first] -= it.second;
        }
        for (auto it : mp1)
        {
            if (it.second <= 0)
            {
                deleteValues.push_back(it.first);
            }
        }
        if (doesntExist == true || mp1.size() - deleteValues.size() > 0)
        {
            cout << "NO\n";
        }
        else
        {
            cout << "YES\n";
        }
    }
}