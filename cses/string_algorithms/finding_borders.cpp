// A border of a string is a prefix that is also a suffix of the string but
// not the whole string.For example, the borders of abcababcab are ab and abcab.

#include <bits/stdc++.h>
using namespace std;
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 1;
int Z[N];
typedef long long int lli;
void z_function(string s)
{
    lli n = s.size();
    int l = 0, r = 0;
    for (auto i = 1; i < n; i++)
    {
        if (i <= r)
            Z[i] = min(Z[i - l], r - i + 1);
        while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]])
            Z[i]++;
        if (i + Z[i] - 1 > r)
        {
            l = i;
            r = i + Z[i] - 1;
        }
    }
}
int main()
{
    string s;
    cin >> s;
    z_function(s);
    for (int i = 0; i < s.size(); i++)
    {
        if (i + Z[i] == s.size())
        {
            cout << i << " ";
        }
    }
}