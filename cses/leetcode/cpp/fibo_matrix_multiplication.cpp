
#include <bits/stdc++.h>
using namespace std;
const int DIM = 2;
const int N = 1e5 + 1;
int dp[N][DIM][DIM];

void multiply(int a[DIM][DIM], int b[DIM][DIM])
{
    // Creating an auxiliary matrix to store elements
    // of the multiplication matrix
    int mul[DIM][DIM];
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            mul[i][j] = 0;
            for (int k = 0; k < DIM; k++)
                mul[i][j] += a[i][k] * b[k][j];
        }
    }

    // storing the multiplication result in a[][]
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            a[i][j] = mul[i][j]; // Updating our matrix
}
void power(int F[DIM][DIM], int n)
{
    dp[1] = F;
    for (int i = 2; i <= n; i++)
    {
        multiply(dp[i / 2], dp[i / 2]);
        if (i % 2 == 1)
        {
            multiply(dp[i], dp[i / 2]);
        }
        else
        {
            dp[i] = dp[i / 2];
        }
    }
}
int main()
{
}