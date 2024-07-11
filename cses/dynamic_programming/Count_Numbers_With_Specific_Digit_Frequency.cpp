/*
There are two integers n, m where 0 ≤ n ≤ m ≤ 1018 . Find the number of integers between
n and m inclusive containing exactly k d digits. n, m, k, d are given in input.
Sample Input
(n, m, k, d) = (7, 111, 2, 1)
This translates to finding the number of integers in the range [7, 111] with exactly two 1
digits. There are three such integers: 11, 101, 110.
*/

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int main(int argc, char const *argv[])
{
    int n, m, k, d;
    cin >> n >> m >> k >> d;
    int dp[20][10][2];
    // dp[i][j][x] = count of digits
    return 0;
}
