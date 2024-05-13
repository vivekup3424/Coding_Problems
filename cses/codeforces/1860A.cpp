#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
typedef std::vector<vector<long long>> vvll;
const int MOD = 1e9 + 7;
const int prime = 31;
const int mod = 1e9 + 9;
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
ll computeHash(string const &s)
{
    ll hash_value = 0;
    ll p_pow = 1;
    for (char c : s)
    {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % mod;
        p_pow = (p_pow * prime) % mod;
    }
    return hash_value;
}

bool isEqual(string const &s1, string const &s2, int start1, int start2, int len)
{
    for (int i = 0; i < len; ++i)
    {
        if (s1[start1 + i] != s2[start2 + i])
        {
            return false;
        }
    }
    return true;
}

bool belongs(string &base, string &substr)
{
    int n = base.size();
    int m = substr.size();
    if (n < m)
        return false;

    ll base_hash = computeHash(base.substr(0, m));
    ll substr_hash = computeHash(substr);

    if (base_hash == substr_hash && isEqual(base, substr, 0, 0, m))
    {
        return true;
    }

    ll p_pow = 1;
    for (int i = 0; i < m; ++i)
    {
        p_pow = (p_pow * prime) % mod;
    }

    for (int i = m; i < n; ++i)
    {
        base_hash = (base_hash - (base[i - m] - 'a' + 1) * p_pow) % mod;
        base_hash = (base_hash + mod) % mod;
        base_hash = (base_hash * prime + (base[i] - 'a' + 1)) % mod;

        if (base_hash == substr_hash && isEqual(base, substr, i - m + 1, 0, m))
        {
            return true;
        }
    }

    return false;
}

int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        string s;
        cin >> s;
        int n = s.size();
        string equal;
        string alternating;
        for (int i = 0; i < n; i++)
        {
            equal.push_back('(');
        }
        for (int i = 0; i < n; i++)
        {
            equal.push_back(')');
        }
        for (int i = 0; i < n; i++)
        {
            alternating.push_back('(');
            alternating.push_back(')');
        }
        bool belongsInEqual = false, belongsInAlternating = false;
        belongsInEqual = belongs(equal, s);
        belongsInAlternating = belongs(alternating, s);
        if (belongsInEqual and belongsInAlternating)
            cout << "NO\n";
        else
        {
            cout << "YES" << endl;
            cout << (belongsInAlternating ? equal : alternating) << endl;
        }
    }
}