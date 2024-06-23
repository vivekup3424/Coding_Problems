
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> m(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int tm;
        cin >> tm;
        m[tm] = i;
    }

    for (int i = 1; i <= n; i++)
    {
        cout << m[i] << " ";
    }
    cout << endl;
    return 0;
}