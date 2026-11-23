/*
 * 1857A. Array Coloring
 * https://codeforces.com/problemset/problem/1857/A
 * Time limit: 1 second | Memory limit: 256 megabytes
 *
 * You are given an array consisting of n integers. You want to color each
 * element of the array either red or blue.
 *
 * Determine whether it is possible to color the elements so that the parity
 * (even or odd) of the sum of the red elements is equal to the parity of the
 * sum of the blue elements.
 *
 * Input:
 *   The first line contains an integer t (1 <= t <= 1000) - the number of
 *   test cases.
 *
 *   The first line of each test case contains an integer n (2 <= n <= 50) -
 *   the length of the array.
 *
 *   The second line contains n integers a_1, a_2, ..., a_n
 *   (1 <= a_i <= 50) - the elements of the array.
 *
 * Output:
 *   For each test case, output "YES" if it is possible to color the elements
 *   as described, and "NO" otherwise. You may print each letter in any case.
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fast_io();
    ll T;
    cin >> T;
    while (T--)
    {
        int n;
        cin>>n;
        int oddCount = 0;
        for (int i = 0; i < n; i++)
        {
            int temp;
            cin>>temp;
            oddCount += (temp&1);
        }
        if (oddCount&1)
        {
            cout<<"NO\n";
        }
        else
        {
            cout<<"YES\n";
        }
    }
}