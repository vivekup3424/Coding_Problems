#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool isMaxHeap(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        if (leftChild < n and arr[i] < arr[leftChild])
        {
            return false;
        }
        if (rightChild < n and arr[i] < arr[rightChild])
        {
            return false;
        }
    }
    return true;
}
