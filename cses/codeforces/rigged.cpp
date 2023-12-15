#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
const int N = 109;
int t;
int n;
vector<int> s(N), e(N);
int main()
{
    fast_io();
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> s[i] >> e[i];
        }
        bool result = true;
        for (int i = 1; i < n; i++)
        {
            if (s[i] >= s[0] and e[i] >= e[0])
            {
                result = false;
            }
                }
        cout << (result == true ? s[0] : -1) << endl;
    }
    return 0;
}