// lexographically minium rotation of a string

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10005;

// Method 1: using string hashing and binary search
// O(nlogn)
int main()
{
    string s;
    cin >> s;
    s += s; // concatenate the string with itself
    int n = s.size();
    // find the lexographically smallest substring of length in the concatenated string using binary search
    int h[n + 1], p[n + 1];
    h[0] = 0;
    p[0] = 1;
    int B = 1e9 + 7;
    int A = 31;
    for (auto i = 1; i <= n; i++) // 1-index based array
    {
        h[i] = (h[i - 1] * A + (s[i - 1] - 'a' + 1)) % B;
        p[i] = (p[i - 1] * A) % B;
    }
    int minimum = INT_MAX, index = 0;
    for (int i = 1; i <= n; i++) // one-indexed
    {
        int substring_hash = h[i + n] - h[i - 1] * p[n];
        if (substring_hash < minimum)
        {
            minimum = substring_hash;
            index = i - 1;
        }
    }
    cout << s.substr(index, n) << endl;
}