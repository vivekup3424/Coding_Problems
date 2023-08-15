// Pre-Computation using Prefix Sum in 1D/2D Arrays |
// Competitive Programming Course | EP 13

/*Given an array a of N integers. Given Q queries and
in each query given L and R, print sum of elments
from index L to R (L and R include)*/

// Since multiple query for data is asked hence there is a scope of
//  pre-computation

// Constraints
// 1 <= N <= 10^5 => int
// 1 <= a[i]<= 10^9=>long long unsinged int
// 1 <= Q <= 10^5 => int
// 1 <= L,R <= N => int

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
const int N = 1e5 + 1;
llu a[N];
// use one-indexed array

// Time-complexity = O(n^2)
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        llu sum = 0;
        for (int i = l; i <= r; i++)
        {
            sum += a[i];
        }
        cout << sum << "\n";
    }
    return 0;
}
// if Q = 10^5 and n = 10^5 => qn = 10^10, hence the runtime > 1 second => TLE

// Method2
// Do pre-computation in finding the sum
// Time-complexity = O(n)
int main2()
{
    int n;
    cin >> n;
    llu forward_sum[n + 1];
    // forward_sum[i] = a[1]+a[2]+...+a[i]
    forward_sum[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        forward_sum[i] = a[i] + forward_sum[i - 1];
    }
    int q;
    cin >> q;
    while (q--)
    {
        int L, R;
        cin >> L >> R;
        int sum = forward_sum[R] - forward_sum[L - 1];
        cout << sum << "\n";
    }
    return 0;
}

// Method 3
// Prefix sum => same as above

// The above method 2 can be called as an instance of DP

// Q.2.
// Given a 2d array of nxn integers. Given Q queries and in each query
// given a,b,c and d print sum of square represented by (a,b) as top-left point
// and (c,d) as bottom-right point

llu N = 1e3 + 1;
llu a[N][N];

int main3()
{
}