#include <bits/stdc++.h>
using namespace std;

const int maxn = 100100;

int n, a[maxn];

void solve()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + n + 1, greater<int>());
    printf("%d\n", a[(n + 1) / 2]);
}

int main()
{
    int T = 1;
    scanf("%d", &T);
    while (T--)
    {
        solve();
    }
    return 0;
}