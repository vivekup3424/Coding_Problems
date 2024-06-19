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
        ll n, k;
        cin >> n >> k;
        if (k % 2 == 1)
        {
            cout << "NO\n";
        }
        else
        {
            vll v;
            for (int i = 1; i <= n; i++)
            {
                v.push_back(i);
            }
            vll temp = v;
            reverse(temp.begin(), temp.end());
            int maxSum = 0;
            for (int i = 0; i < n; i++)
            {
                maxSum += abs(temp[i] - v[i]);
            }
            if (k > maxSum)
            {
                cout << "NO\n";
            }
            else
            {
                int l = 0, r = n - 1;
                while (k > 0)
                {
                    if (k >= 2 * abs(v[l] - v[r]))
                    {
                        k -= 2 * abs(v[l] - v[r]);
                        swap(v[l], v[r]);
                        l++;
                        r--;
                    }
                    else
                    {
                        for (int i = l; i <= r; i++)
                        {
                            if (k == 2 * abs(v[l] - v[i]))
                            {
                                swap(v[l], v[i]);
                                l++;
                                k -= 2 * abs(v[l] - v[i]);
                                break;
                            }
                        }
                    }
                }
                cout << "YES\n";
                outputVector(v, n);
            }
        }
    }
}