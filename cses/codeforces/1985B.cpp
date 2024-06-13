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
        vector<bool> sieve(n + 1, false);
        ll maxSum = 0, maxPrime = 0;
        for (int i = 2; i < sieve.size(); i++)
        {
            if (sieve[i] == false)
            {
                ll x = i;
                ll sum = 0;
                while (x < sieve.size())
                {
                    sieve[x] = true;
                    sum += x;
                    if (sum > maxSum)
                    {
                        maxPrime = i;
                        maxSum = sum;
                    }
                    x += i;
                }
            }
        }
        cout << maxPrime << endl;
    }
}