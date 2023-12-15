// Must Know Concept in Pre-Computation
// for every Competitive Programmer | CP Course | EP 15

// Q.
// https://www.hackerrank.com/challenges/crush/problem
// Starting with a 1-indexed array of zeros and a list of operations,
// for each operation add a value to each the array element between
// two given indices, inclusive. Once all operations have been performed,
// return the maximum value in the array.
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
const llu N = 1e7 + 1;
llu arr[N];
//  holds 0 as default value, 1 indexed

// Method 1
// Time complexity = O(n*n+n) = O(n^2)
// Try to make it linear
// Think of hashing, prefix or precomputation

int main1()
{
    fast_io();
    int n, m;
    cin >> n >> m;
    while (m--)
    {
        int a, b, d;
        cin >> a >> b >> d;
        for (int i = a; i <= b; i++)
        {
            arr[i] += d;
        }
    }
    llu max = 0;
    for (int i = 1; i <= n; i++)
    {
        if (max < arr[i])
            max = arr[i];
    }
    cout << max;
}

// Prefix Sum
// Scanline Algorithm
int main2()
{
    fast_io();
    int n, m;
    cin >> n >> m;
}