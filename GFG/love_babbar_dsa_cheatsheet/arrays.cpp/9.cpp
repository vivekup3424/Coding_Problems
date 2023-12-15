// minimize the maximum difference between the heights

// Given the heights of N towers and a value of K, Either increase or
// decrease the height of every tower by K(only once) where K > 0.
// After modifications, the task is to minimize the difference
// between the heights of the longest and the shortest tower
// and output its difference.
#include <bits/stdc++.h>
using namespace std;
int getMinDiff(vector<int> v, int length, int k)
{
    sort(v.begin(), v.end());
    int max_diff = arr[length - 1] - arr[0];
    int temp_min = arr[0], temp_max = arr[length - 1];
    int key = -1, ans = INT_MAX;
    for (int i = 0; i < length; i++)
    {
        if (v[i] <= k)
        {
            temp_min = min(arr[0] + k, arr[i] - k);
            temp_max = max(arr[i - 1] + k, arr[n - 1] + k)
                ans = min(ans, temp_max - temp_min);
        }
        else if (v[i] > k)
            break;
    }
}