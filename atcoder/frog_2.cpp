/**
 *Problem Statement

There are
N stones, numbered 1,2,…,N. For each i (1≤i≤N), the height of Stone i is

hi​.

There is a frog who is initially on Stone
1. He will repeat the following action some number of times to reach Stone

* N :


    If the frog is currently on Stone

i, jump to one of the following: Stone i+1,i+2,…,i+K. Here, a cost of ∣hi​−hj​∣ is incurred, where

    j is the stone to land on.

Find the minimum possible total cost incurred before the frog reaches Stone
N
 */
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, k;
    cin >> n >> k;
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
        else
        {
            int maxi = INT_MAX;
            for (int j = 1; j <= k; j++)
            {
                if (i - j < 0)
                {
                    break;
                }
                else
                {
                    maxi = min(maxi, abs(heights[i] - heights[i - j]) + dp[i - j]);
                }
            }
            dp[i] = maxi;
        }
    }
    cout << dp[n - 1] << endl;
}
