#include <bits/stdc++.h>
using namespace std;
/**
 * Problem = Given two sorted arrays of sizes m and n respectively, the task is to find the element that would be at the k-th position in the final sorted array formed by merging these two arrays.
 */

// Method 1
/*
[Naive Approach] Merge Two Sorted Arrays using Sorting – O(m + n) time and O(m + n) auxiliary space:
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

// Method 2
/*
[Better approach] Space Optimized Two pointers Merge Approach –
O(k) time and
O(1) auxiliary space:
*/
/*
This approach optimizes the space complexity of the
above naive approach by avoiding the creation of
an additional array. Instead, we use two pointers
to traverse the input arrays and count the elements
until we reach the k-th element.
*/
int kth_two_pointers(int arr1[], int arr2[], int k)
{
    int n = sizeof(arr1) / sizeof(int);
    int m = sizeof(arr2) / sizeof(int);
    int d = 0, i = 0, j = 0;
    while (i < n and j < m)
    {
        if (arr1[i] < arr2[j])
        {
            d++;
            if (d == k)
            {
                return arr1[i];
            }
            i++;
        }
        else
        {
            d++;
            if (d == k)
            {
                return arr2[j];
            }
            j++;
        }
    }
    while (i < m)
    {
        d++;
        if (d == k)
        {
            return arr1[i];
        }
        i++;
    }
    while (j < n)
    {
        d++;
        if (d == k)
        {
            return arr2[j]++;
        }
        j++;
    }
    return -1;
}