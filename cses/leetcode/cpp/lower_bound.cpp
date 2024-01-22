
#include <bits/stdc++.h>
using namespace std;
// using binary search
int lowerBound(vector<int> arr, int n, int x)
{
    int ans = n;
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        if (arr[m] >= x)
        {
            // probable ans could be m
            ans = m;
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }
    return ans;
}
// using stl
int lowerBound1(vector<int> arr, int n, int x)
{
    int lower_bound_index = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
    // Time Complexity = O(logn)
}

// implementing upper bounded
// smallest index such that the number at that index is strictly greater than x

int upperBound(vector<int> &arr, int x, int n)
{
    int ans = n;
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        if (arr[m] > x)
        {
            // if arr[m] > x, => m could be our possible answer
            ans = m;
            r = m - 1;
        }
        else if (arr[m] <= x)
        {
            l = m + 1;
        }
    }
    return ans;
}
int upperBound1(vector<int> arr, int x, int n)
{
    return upper_bound(arr.begin(), arr.end(), x) - arr.begin();
}
int main()
{
}