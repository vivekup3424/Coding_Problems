// rabin-karp algorithm for pattern searching

// it uses the concept of polynomial hashing and sliding window combined

// program below

#include <bits/stdc++.h>
using namespace std;
const int A = 31;
const int B = 1e9 + 9;
const int N = 1e6 + 1;
int h[N], p[N];
int get_value(char c)
{
    return c - 'a' + 1;
}
int get_hash(string s)
{
    int hash_value = 0;
    for (auto c : s)
    {
        int value = get_value(c);
        hash_value = (hash_value * A + value) % B;
    }
    return hash_value;
}
void precompute_hash(string s)
{
    h[0] = get_value(s[0]);
    p[0] = 1;
    for (auto i = 1; i <= s.size(); i++)
    {
        h[i] = (h[i - 1] * A + get_value(s[i])) % B;
        p[i] = (p[i - 1] * A) % B;
    }
}
void rabin_karp(string s, string pattern)
{
    int n = s.size(), m = pattern.size();
    int pattern_hash = get_hash(pattern);
    precompute_hash(s);
    for (auto i = m; i <= n; i++)
    {
        int hash_substring = (h[i - 1] - h[i - m] * p[m - 1]) % B;
        if (hash_substring == pattern_hash)
            cout << i - m << endl;
    }
}
int main()
{
    string s, pattern;
    cin >> s >> pattern;
    rabin_karp(s, pattern);
    return 0;
}