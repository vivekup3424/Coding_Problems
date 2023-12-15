#include <bits/stdc++.h>
using namespace std;
// range minimum query (inclusive indices)
const int MAX_N = 1e6 + 5;
const int LOG = 17;
int a[MAX_N];
int m[MAX_N][LOG]; // m[i][j] is the minimum amount a[i] to a[i + 2^*(j-1)]
int query(int L, int R)
{
    int length = R - L + 1;
    // get the log of length
    int k = 0;
    while (length > 0)
    {
        k++;
        length >>= 1;
    }
    return min(m[L][k], m[R - (1 << k) + 1][k]);
}
int main()
{
    // 1. read input
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        m[i][0] = a[i]; // base case here
    }

    // preprocessing, building the sparse table
    for (int j = 0; j < LOG; j++)
    {
        for (int i = 0; i + (1 << j) - 1 < n; i++)
        {
            m[i][j] = min(m[i][j - 1], m[i + (1 << (j - 1))][j - 1]);
        }
    }

    // answering the range minimum queries
}