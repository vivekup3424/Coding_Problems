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
    T = 1;
    while (T--)
    {
        ll n;
        cin >> n;
        vector<pair<ll, ll>> v(n);
        // Each line has two integers a and d: the duration and deadline of the task.
        for (int i = 0; i < n; i++)
        {
            cin >> v[i].first >> v[i].second;
        }
        sort(v.begin(), v.end());
        ll sum = 0;
        ll time = 0;
        for (int i = 0; i < n; i++)
        {
            time += v[i].first;
            sum += (v[i].second - time);
        }
        cout << sum << endl;
    }
}