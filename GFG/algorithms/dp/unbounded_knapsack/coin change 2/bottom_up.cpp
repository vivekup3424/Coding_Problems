#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;

// minimum number of coins to form a total sum
/*
Given a sum S, if we want to make a change for S cents, and
we have an infinite supply of each of n = { C1, C2, .., Cm}
valued coins, what is the minimum number of coins to make
the change? If it’s not possible to make a change, print -1.
*/
int minimumCoins(int coins[], int n, int sum)
{
    int t[n + 1][sum + 1];
    memset(t, -1, (n + 1) * (sum + 1));
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < sum + 1; j++)
        {
        }
    }
}