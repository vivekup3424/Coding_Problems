#include <iostream>
using namespace std;

// Coin Change Problem Maximum Number of ways
// Given a value N, if we want to make change for N cents, and
// we have infinite supply of each of S = { S1, S2, .. , Sm} valued coins,
// how many ways can we make the change? The order of coins doesn’t matter.

int CountMaxSubsetCoins(int coins[], int Sum, int n) // n = number of(types) coins
{
    if (Sum == 0)
        return 1; // Base Case
    else if (n == 0)
        return 0; // Base Case
    else if (coins[n - 1] > Sum)
        return CountMaxSubsetCoins(coins, Sum, n - 1);
    else
    {
        // including the nth coin and not including the nth coin
        return CountMaxSubsetCoins(coins, Sum - coins[n - 1], n) + CountMaxSubsetCoins(coins, Sum, n - 1);
    }
    // Time Complexity = O(2^Sum), Space Complexity = O(n)
}