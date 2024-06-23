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
        ll n, m;
        cin >> n >> m;
        string a;
        cin >> a; // len(a) = n
        vll v(m);
        inputVector(v, m);
        sort(v.begin(), v.end());
        string b;
        cin >> b;
        sort(b.begin(), b.end());
        int count = 0;
        set<int> visited;
        for (int i = 0; i < m; i++)
        {
            if (visited.count(v[i]) == 0)
            {
                a[v[i] - 1] = b[count];
                visited.insert(v[i]);
                count++;
            }
        }
        cout << a << endl;
    }
}