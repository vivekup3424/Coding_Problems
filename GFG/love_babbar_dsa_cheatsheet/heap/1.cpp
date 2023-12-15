// Building heap from array

// Given an array of N elements.
// The task is to build a Binary Heap from the given array.
// The heap can be either Max Heap or Min Heap

// Assumption for the heap formed from the array
// 1. Root is at index 0 in array
// 2. Left child of the ith node is at (2*i +1) index
// 3. Right child of the ith node is at (2*i +2) index
// 4. Parent of the ith node is at (i-1)/2 index
// The same can be said about BST formed from array
#include <bits/stdc++.h>
using namespace std;
// Method 1
// Takes O(nlogn) time complexity

// Method 2
// Takes O(n) time complexity

// heapifies subtree rooted at node of index i
void heapify(vector<int> arr, int N, int i) // N is the length of the array
{
    int largest = i;   // initizlize largest at root
    int l = 2 * i + 1; // left-child
    int r = 2 * i + 2; // right-child

    // if left-child is larger than root
    if (l < N and arr[l] > arr[largest])
    {
        largest = l;
    }
    // if right-child is larger than root
    if (r < N and arr[r] > arr[largest])
    {
        largest = r;
    }

    // if largest is not root, then swap largest and root
    if (largest != i)
    {
        swap(arr[largest], arr[i]);
    }

    // Recursively heapify the affected subtree
    heapify(arr, N, largest);
}

// builds max-heap
void buildMaxHeap(vector<int> arr, int N)
{
    // index of last node leaf-node = index of parent of last leaf-node
    int startIndex = N / 2 - 1;

    // perform reverse-level order traversal from startIndex and heapify each node
    for (int i = startIndex; i >= 0; i--)
    {
        heapify(arr, N, i);
    }
}

void printHeap(vector<int> arr, int N)
{
    cout << "Array representation of Heap is:\n";

    for (int i = 0; i < N; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

// Driver Code
int main()
{
    // Binary Tree Representation
    // of input array
    //             1
    //           /    \
    //         3        5
    //       /  \     /  \
    //     4      6  13  10
    //    / \    / \
    //   9   8  15 17
    vector<int> arr = {1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};

    int N = sizeof(arr) / sizeof(arr[0]);

    // Function call
    buildMaxHeap(arr, N);
    printHeap(arr, N);

    // Final Heap:
    //              17
    //            /    \
    //          15      13
    //         /  \     / \
    //        9     6  5   10
    //       / \   / \
    //      4   8 3   1

    return 0;
}