/*
 * 1873C. Target Practice
 * https://codeforces.com/problemset/problem/1873/C
 * Time limit: 1 second | Memory limit: 256 megabytes
 *
 * A 10 x 10 target is made up of five concentric rings. The outermost ring
 * is worth 1 point, the next ring is worth 2 points, and so on, up to the
 * innermost ring (the centre 2 x 2 square), which is worth 5 points.
 *
 * Given a 10 x 10 grid showing where arrows landed, find the total score.
 * A cell marked 'X' is an arrow that hit that cell, and its score is the
 * value of the ring that cell belongs to. A cell marked '.' is empty and
 * scores nothing. Each cell contains at most one arrow.
 *
 * Input:
 *   The first line contains an integer t (1 <= t <= 1000) - the number of
 *   test cases.
 *
 *   Each test case consists of 10 lines, each containing 10 characters. Each
 *   character is either 'X' (an arrow hit this cell) or '.' (no arrow).
 *
 * Output:
 *   For each test case, output a single integer - the total score of all
 *   arrows on the target.
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
    }
}
