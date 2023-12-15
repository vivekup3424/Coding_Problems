// write a program to cyclically rotate a array by one

// I am going to use for this

// Examples:
// Input:  arr[] = {1, 2, 3, 4, 5}
// Output: arr[] = {5, 1, 2, 3, 4}

#include <bits/stdc++.h>
using namespace std;
void rearrange(vector<int> &arr, int n)
{
    int x = arr[n - 1], i;
    for (i = n - 1; i > 0; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[0] = x;
}