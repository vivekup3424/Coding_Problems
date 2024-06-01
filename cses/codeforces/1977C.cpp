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
        sort(a.begin(), a.end());
        vll temp;
        ll maxIdx = -1;
        for (int i = n - 1; i >= 0; i--)
        {
            ll element = a[i];
            for (int j = i - 1; j >= 0; j--)
            {
                if (element % a[j] != 0)
                {
                    temp.push_back(element);
                    maxIdx = i;
                    break;
                }
            }
        }
        // collect all elements smaller than maxIdx(element)
        for (int j = maxIdx - 1; j >= 0; j--)
        {
            temp.push_back(a[j]);
        }
        outputVector(temp, temp.size());
        cout << temp.size() << endl;
    }
}