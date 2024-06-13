// Given an infinite supply of n types of coins,
// and a given sum, we have to find minimum number of coins to form that sum

#include <bits/stdc++.h>
using namespace std;
int minimumCoins(vector<int> v, int n, int sum) // n is the number of types of coins
{
    if (sum == 0)
    {
        return 1;
    }
    else if (n == 0)
    {
        return 0;
    }
    else if (v[n - 1] > sum)
    {
        return minimumCoins(v, n - 1, sum);
    }
    else if (v[n - 1] <= sum)
    {
        return min((1 + minimumCoins(v, n, sum - v[n - 1])), minimumCoins(v, n - 1, sum));
    }
}
int main()
{
    int n, k; // K is sum
    cin >> n >> k;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    int result = minimumCoins(v, n, k);
    cout << result << "\n";
    return 0;
}