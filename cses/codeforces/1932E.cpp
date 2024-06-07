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
        string s;
        cin >> s;
        for (int i = 0; i < n; i++)
        {
            v[i] = s[i] - '0';
        }
        vll pref(n);
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                pref[0] = v[0];
            }
            else
            {
                pref[i] = v[i] + pref[i - 1];
            }
        }
        // building up the ans
        ll carry = 0;
        vll ans;
        for (int i = n - 1; i >= 0; i--)
        {
            ll sum = pref[i] + carry;
            carry = sum / 10;
            ans.push_back(sum % 10);
        }
        while (carry > 0)
        {
            ans.push_back(carry % 10);
            carry = carry / 10;
        }
        reverse(ans.begin(), ans.end());
        // trim the leading zeroes
        int i = 0;
        for (; i < ans.size(); i++)
        {
            if (ans[i] != 0)
            {
                break;
            }
            else
            {
                continue;
            }
        }
        for (; i < ans.size(); i++)
        {
            cout << ans[i];
        }
        cout << endl;
    }
}