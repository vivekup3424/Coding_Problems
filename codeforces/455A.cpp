
#include </bits/stdc++.h>
using namespace std;

#define ll long long int

ll dp[100005];
ll freq[100005];
int main()
{
    int n, mx = 0;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        freq[a[i]]++;
        mx = max(mx, a[i]);
    }

    dp[1] = freq[1];
    for (int i = 2; i <= mx; i++)
    {
        dp[i] = max((dp[i - 2] + (freq[i] * i)), dp[i - 1]);
    }
    cout << dp[mx];

    return 0;
}