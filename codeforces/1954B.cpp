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
        vll v(n, 0);
        inputVector(v, n);
        int first_value = v.front(),
            back_value = v.back();
        int current_length = 0, min_length = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (v[i] == first_value)
            {
                current_length++;
            }
            else if (v[i] != first_value or i == n - 1)
            {
                min_length = min(min_length, current_length);
                current_length = 0;
            }
        }
        {
            cout << (min_length == n ? -1 : min_length) << endl;
        }
    }
}