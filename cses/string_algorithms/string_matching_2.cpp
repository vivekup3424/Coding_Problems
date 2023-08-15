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
    string s, p;
    cin >> s >> p;
    string temp = p + "$" + s;
    z_function(temp);
    int counter = 0;
    for (auto i = 0; i < temp.size(); i++)
    {
        if (Z[i] == p.size())
            counter++;
    }
    cout << counter << endl;
    return 0;
}
