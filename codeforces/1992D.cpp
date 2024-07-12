#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    int tt;
    cin >> tt;
    while (tt--)
    {
        int n, m, k;
        cin >> n >> m >> k;
        string s;
        cin >> s;
        s = "L" + s + "L";
        n += 2;
        bool ok = true;
        int at = 0;
        while (at < n - 1)
        {
            if (s[at] == 'L')
            {
                bool found = false;
                for (int i = at + 1; i < n && i <= at + m; i++)
                {
                    if (s[i] == 'L')
                    {
                        at = i;
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    at += m;
                    if (s[at] == 'C')
                    {
                        ok = false;
                        break;
                    }
                }
            }
            else
            {
                at += 1;
                if (s[at] == 'C')
                {
                    ok = false;
                    break;
                }
                k -= 1;
            }
        }
        cout << (ok && k >= 0 ? "YES" : "NO") << '\n';
    }
    return 0;
}