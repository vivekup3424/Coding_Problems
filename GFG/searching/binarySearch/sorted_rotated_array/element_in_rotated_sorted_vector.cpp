// Given a sorted and rotated array arr[] of size N and a key,
// the task is to find the key in the array. (return index of key in rotated array)

#include <bits/stdc++.h>
using namespace std;
// Now we can use binary search
int number_of_rotations(vector<int> V)
{
    int N = V.size();
    // index of minimum element would return the number of rotations
    int low = 0, high = N - 1;

    // If there is only one element
    if (V[low] <= V[high])
        return 0;
    int mid = low + (high - low) / 2;
    int result = -1;
    while (low < high)
    {
        // if first element is mid or
        // last element is mid
        // then simply use modulo so it
        // never goes out of bound.
        int prev = (mid - 1 + N) % N; //((mid-1+N)%N == (mid-1)%N)
        int next = (mid + 1) % N;
        if (V[mid] < V[prev] && V[mid] < V[next])
        {
            result = mid;
            break;
        }
        else if (V[mid] > V[mid - 1])
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return result;
}

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
#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> V = {15,
                     18,
                     2,
                     3,
                     6,
                     12};
    int value = 6;
    int no_rotations = number_of_rotations(V);
    cout << no_rotations << endl;
    int min_index = number_of_rotations(V);
    int first_index = binarySearch(V, 0, min_index, value);
    int second_index = binarySearch(V, min_index + 1, V.size() - 1, value);
    int index = max(first_index, second_index);
    cout << index << "\n";
    return 0;
}
// Time Complexity: O(log N)
// Auxiliary Space : O(1), since no extra space has been taken.