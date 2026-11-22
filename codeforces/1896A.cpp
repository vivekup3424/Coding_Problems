/*
 * 1896A. Jagged Swaps
 * https://codeforces.com/problemset/problem/1896/A
 * Time limit: 1 second | Memory limit: 256 megabytes
 *
 * You are given a permutation a of size n. You can do the following
 * operation:
 *
 *   - Select an index i from 2 to n - 1 such that a[i-1] < a[i] and
 *     a[i] > a[i+1]. Swap a[i] and a[i+1].
 *
 * Determine whether it is possible to sort the permutation after a finite
 * number of operations.
 *
 * A permutation is an array consisting of n distinct integers from 1 to n
 * in arbitrary order.
 *
 * Input:
 *   Each test contains multiple test cases. The first line contains a single
 *   integer t (1 <= t <= 5000) - the number of test cases. Description of
 *   the test cases follows.
 *
 *   The first line of each test case contains a single integer n
 *   (3 <= n <= 10) - the size of the permutation.
 *
 *   The second line of each test case contains n integers a_1, a_2, ..., a_n
 *   (1 <= a_i <= n) - the elements of permutation a.
 *
 * Output:
 *   For each test case, print "YES" if it is possible to sort the
 *   permutation, and "NO" otherwise.
 *
 *   You may print each letter in any case.
 *
 * Example 1:
 *   Input:
 *     6
 *     3
 *     1 2 3
 *     5
 *     1 3 2 5 4
 *     5
 *     5 4 3 2 1
 *     3
 *     3 1 2
 *     4
 *     2 3 1 4
 *     5
 *     5 1 2 3 4
 *   Output:
 *     YES
 *     YES
 *     NO
 *     NO
 *     NO
 *     NO
 *
 * Note:
 *   In the first test case, the permutation is already sorted.
 *
 *   In the second test case, we can choose index i = 2 as 1 < 3 and 3 > 2 to
 *   form [1, 2, 3, 5, 4]. Then we can choose index i = 4 as 3 < 5 and 5 > 4
 *   to form [1, 2, 3, 4, 5].
 *
 *   In the third test case, it can be proven that it is impossible to sort
 *   the array.
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
        ll n;
        cin>>n;
        vector<ll> v;
        for (auto i = 0; i < n; i++)
        {
            int temp;
            cin>>temp;
            v.push_back(temp);
        }
        cout<<(v[0] == 1 ? "YES" : "NO")<<"\n";
    }
}
