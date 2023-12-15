#include <bits/stdc++.h>
using namespace std;
int max(int a, int b)
{
    if (a >= b)
        return a;
    else
        return b;
}

// Given a rod of length n inches and an array of prices that contains prices of
// all pieces of size smaller than n.Determine the maximum value obtainable by
// cutting up the rod and selling the pieces.

int length[8] = {1, 2, 3, 4, 5, 6, 7, 8};
int price[8] = {1, 5, 8, 9, 10, 17, 17, 20};
static int L = 8; // L = length of rod
// we have to get maximum price
// n = no of pieces

int max_rod(int length[], int price[], int L, int n)
{
    if (L == 0 || n == 0)
        return 0;
    else if (length[n - 1] > L)
        return max_rod(length, price, L, n - 1);
    else if (length[n - 1] <= L)
    {
        return max(price[n - 1] + max_rod(length, price, L - length[n - 1], n),
                   max_rod(length, price, L, n - 1));
    }
}
int main()
{
    cout << max_rod(length, price, 8, 8) << "\n";
}