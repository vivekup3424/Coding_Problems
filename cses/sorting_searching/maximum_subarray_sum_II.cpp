// Given an array of n integers, your task is to find the
// maximum sum of values in a contiguous subarray with
// length between a and b.

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
    int n, a, b;
    cin >> n >> a >> b;
    vector<lli> pfx(n + 1); // prefix sum
    pfx[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        pfx[i] = a + pfx[i - 1];
    }
    // now I have done that prefix sum computation
    lli ret = INT_MIN
        multiset<lli>
            ms;
    for (int i = a; i <= N; i++)
    {
        if (i > b)
            ms.erase
    }
}