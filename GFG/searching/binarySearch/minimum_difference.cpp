// Minimum Difference Element in a Sorted Array

// Given a sorted array, find the element in the array which
// has minimum difference with the given number.

#include <bits/stdc++.h>
using namespace std;

// Method 1 find the floor and ceil of the element and the least difference from them
// Time Complexity:- O(logn)

// Method 2
// If you analyze the binary search algorithm carefully, then you will find that at the end
// of the loop, the start and end indices point to the numbers that are closest to the
// target value being searched for. So essentially, at the end of the loop, the start
// index points to the ceiling of the target and the end index points to the floor of
// the target value.

int minimum_difference(vector<int> V, int value)
{
    if (V.size() == 1)
        return abs(V[0] - value);
    int low = 0, high = V.size() - 1;
    int mid;
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        if (value == V[mid])
            return 0;
        else if (value > V[mid])
            low = mid + 1;
        else if (value < V[mid])
            high = mid - 1;
    }
    int diff = min(abs(value - V[low]), abs(V[low + 1] - value));
    return diff;
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
    int diff = minimum_difference(V, K);
    cout << diff << "\n";
    return 0;
}