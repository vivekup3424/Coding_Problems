// Given a sorted array arr[] and a number x,
// write a function that counts the occurrences of x in arr[].
// Expected time complexity is O(Logn)

// Method 1. We can traverse the array and count the number of occurrences of
// the array by simple traversal O(n)

// Method 2. We can use binary search to find the first and last occurence
// of the repeated element and hence find the count of total number of occurences

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
int first_occurence(vector<int> v, int value)
{
    int low = 0, high = v.size() - 1, mid = low + (high - low) / 2;
    int first_occurence = -1;
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        if (value == v[mid])
        {
            first_occurence = mid;
            high = mid - 1; // moving the pointer to left
            // return mid;
        }
        else if (value < v[mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    // now for first occurrence
    return first_occurence;
}
int last_occurence(vector<int> v, int value)
{
    int low = 0, high = v.size() - 1, mid = low + (high - low) / 2;
    int last_occurence = -1;
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        if (value == v[mid])
        {
            last_occurence = mid;
            low = mid + 1; // moving the pointer to right
            // return mid;
        }
        else if (value < v[mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    // now for last occurrence
    return last_occurence;
}
pair<int, int> first_and_last_occurence(vector<int> v, int value)
{
    int first_occur = first_occurence(v, value);
    int last_occur = last_occurence(v, value);
    pair<int, int> result(first_occur, last_occur);
    return result;
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
    pair<int, int> result = first_and_last_occurence(V, K);
    if (result.first == -1 || result.second == -1)
    {
        cout << "0\n";
    }
    else
    {
        int answer = result.second - result.first + 1;
        cout << answer << "\n";
    }
    return 0;
}
// Time Complexity:- O(logn)
// Auxilliary Space:- O(1), as we are only saving variables