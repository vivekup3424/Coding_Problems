// 7 Number of Times a Sorted array is Rotated -Aditya Verma(Binary Search)

// Find the Rotation Count in Rotated Sorted array
//     Consider an array of distinct numbers sorted in
//     increasing order.The array has been
//     rotated(clockwise)
// k number of times.Given such an array, find the value of k.

// Method 1 Linear Traversal, find the index of minimum number => num
// of cylces

// Follow the steps mentioned below to implement the idea :
//
//     Initialize two variables to store the minimum value and the index
//     of that value.Traverse the array from start to the end :
//     Find the minimum value and index where the minimum value is stored.
//     Return the index of the minimum value.

/*
// C++ program to find number of rotations
// in a sorted and rotated array.
#include <bits/stdc++.h>
using namespace std;

// Returns count of rotations for an array which
// is first sorted in ascending order, then rotated
int countRotations(int arr[], int n)
{
    // We basically find index of minimum
    // element
    int min = arr[0], min_index = 0;
    for (int i = 0; i < n; i++)
    {
        if (min > arr[i])
        {
            min = arr[i];
            min_index = i;
        }
    }
    return min_index;
}

// Driver code
int main()
{
    int arr[] = {15, 18, 2, 3, 6, 12};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << countRotations(arr, n);
    return 0;
}
//Time Complexity: O(N)
//Auxiliary Space: O(1)
*/

/**********************************/

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
    int no_rotations = number_of_rotations(V);
    cout << no_rotations << endl;
    return 0;
}
// Time Complexity: O(log N)
// Auxiliary Space : O(1), since no extra space has been taken.