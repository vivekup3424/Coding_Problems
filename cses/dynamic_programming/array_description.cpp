#include <bits/stdc++.h>
using namespace std;
int recurse(vector<int> a, int n, int m, int i)
{
    if (i == 0)
    {
        if (a[i] == 0)
        {
            return m;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if (a[i] == 0)
        {
            int count = 0;
            int v = a[i - 1];
            if (v - 1 > 0)
            {
                a[i] = v - 1;
                count += recurse(a, n, m, i - 1);
            }
            if (v + 1 <= m)
            {
                a[i] = v + 1;
                count += recurse(a, n, m, i - 1);
            }
            a[i] = v;
            count += recurse(a, n, m, i - 1);
            return count;
        }
        else
        {
            return recurse(a, n, m, i - 1);
        }
    }
}
int main(int argc, char const *argv[])
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    return 0;
}
