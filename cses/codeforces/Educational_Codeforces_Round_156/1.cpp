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
int main()
{
    fast_io();
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        stack<int> s;
        int start = 0;
        while (start < n and s.size() < 3)
        {
            start++;
            s.push(start);
            while (s.top() % 3 != 0)
            {
                s.pop();
                start++;
                s.push(start);
            }
        }
        vector<int> v;
        while (s.empty() == false)
        {
            int t = s.top();
            if (t % 3 == 0)
            {
                cout << "NO" << endl;
                return 0;
            }
            else
            {
                v.push_back(t);
                s.pop();
            }
        }
    }

    return 0;
}