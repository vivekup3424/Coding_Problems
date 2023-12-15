// Find the “Kth” max and min element of an array

// Method 1
// Do the sorting of the array in O(nlogn) time and
// Find the kth max and min element

// Method 2
// We use max-heap
//
#include <bits/stdc++.h>
using namespace std;

// returns (min,max)
pair<int, int> first_method(vector<int> arr, int length, int k)
{
    // assuming the arrai is sorted
    if (k > length)
    {
        cout << "invalid input\n";
        return pair<int, int>(-1, -1);
    }
    else
    {
        int min = (k - 1);
        int max = length - k;
        pair<int, int> result(min, max);
        return result;
    }
}

// Method 2
//  returns (min,max)
//  Use randomized quickselect algo
// expected linear time

// returns a random index between l and r (inclusively)
int randomPartition(vector<int> arr, int l, int r); // l = left_index, r = right_index

int kthsmallest(vector<int> arr, int l, int r, int k)
{
    // If k is smaller than number of elements the array
    if (k >= 0 and k <= r - l + 1)
    {
        // Partition the array about a random element and
        // get the posisiton of pivot element in the array
        int pos = randomPartition(arr, l, r);

        // if pos is same as k
    }
}

// Method 3
// Use heap