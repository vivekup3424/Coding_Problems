// Seraching an element in bitonic array
// Given a bitonic sequence of n distinct elements, and an integer x,
// the task is to write a program to find given element x in the bitonic sequence in O(log n) time.

////////////////////////////////////////////////////
// This can be done by linear traversal

// This can also be done by:-
// 1.Find the pivot element can see if the required elment is at which side of pivot element
// 2.Do the binary search on that side of pivot element only

#include <bits/stdc++.h>
using namespace std;

// returns the index of the element found
int binarySearch(vector<int> v, int low, int high, int value)
{
    // int low = 0, high = v.size() - 1;
    int mid;
    bool result = false;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (value == v[mid])
        {
            result = true;
            return mid;
        }
        if (value < v[mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    if (!result)
        return -1;
}
int peak_index(vector<int> v)
{
    int low = 0, high = v.size() - 1, mid;
    if (v.size() == 1)
        return v[0];
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        // first case if mid is the answer
        if ((mid == 0 || v[mid - 1] < v[mid]) and (mid == v.size() - 1 || v[mid + 1] < v[mid]))
        {
            return mid;
        }
        else if (v[mid] > v[mid + 1])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
}

int find_index(vector<int> bitonic, int value)
{
    int peak_ind = peak_index(bitonic);
    int results = -1;
    if (value == bitonic[peak_ind])
        results = peak_ind;
    else if (value < bitonic[peak_ind])
    {
        results = binarySearch(bitonic, 0, peak_ind, value);
    }
    else
    {
        results = binarySearch(bitonic, peak_ind + 1, bitonic.size() - 1, value);
    }
    return results;
}
int main()
{
    int N, K;
    cin >> N >> K;
    vector<int> V(N);
    for (int i = 0; i < N; i++)
    {
        cin >> V[i];
    }
    int index = find_index(V, K);
    cout << index << "\n";
    return 0;
}
