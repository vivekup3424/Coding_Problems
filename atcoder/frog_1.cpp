/*
Problem Statement

There are
N stones, numbered 1,2,…,N. For each i (1≤i≤N), the height of Stone i is

hi​.

There is a frog who is initially on Stone
1. He will repeat the following action some number of times to reach Stone

N:

    If the frog is currently on Stone

i, jump to Stone i+1 or Stone i+2. Here, a cost of ∣hi​−hj​∣ is incurred, where

    j is the stone to land on.

Find the minimum possible total cost incurred before the frog reaches Stone
N.
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> heights(n);
    for (int i = 0; i < n; i++)
    {
        cin >> heights[i];
    }
    vector<int> dp(n, 0);
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            dp[i] = 0;
        }
        else if (i == 1)
        {
            dp[i] = abs(heights[i] - heights[i - 1]);
        }
        else
        {
            dp[i] = min(abs(heights[i] - heights[i - 1]) + dp[i - 1], abs(heights[i] - heights[i - 2]) + dp[i - 2]);
        }
    }
    cout << dp[n - 1] << endl;
}