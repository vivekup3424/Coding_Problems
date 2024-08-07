#include <bits/stdc++.h>
using namespace std;
/**
 * Problem = Given two sorted arrays of sizes m and n respectively, the task is to find the element that would be at the k-th position in the final sorted array formed by merging these two arrays.
 */

// Method 1
/*
[Naive Approach] Merge Two Sorted Arrays using Sorting – O((m + n) * log(m + n)) time and O(m + n) auxiliary space
*/

int kth_sorted(int arr1[], int arr2[], int k)
{
    int n = sizeof(arr1) / sizeof(arr1[0]);
    int m = sizeof(arr2) / sizeof(arr2[0]);
    int sorted1[n + m];
    int i = 0, j = 0, d = 0;
    while (i < n && j < m)
    {
        if (arr1[i] < arr2[j])
        {
            sorted1[d++] = arr1[i++];
        }
        else
        {
            sorted1[d++] = arr2[j++];
        }
    }
    while (i < n)
    {
        sorted1[d++] = arr1[i++];
    }
    while (j < m)
    {
        sorted1[d++] = arr2[j++];
    }
    return sorted1[k - 1];
}