/*Given an array of integers and a number k, find the maximum sum of a subarray of size k. */
#include <iostream>
using namespace std;
// O(n) solution for finding maximum sum of
// a subarray of size k

// Returns maximum sum in a subarray of size k.
int maxSum(int arr[], int n, int k)
{
    // k must be smaller than n
    if(n<k)
    {
        cout<<"Invalid \n";
        return -1;
    }
    
    // Compute sum of first window of size k
    int sum_so_far = 0;
    for (int i = 0; i < k; i++)
    {
        sum_so_far += arr[i];
    }
    // Compute sums of remaining windows by
    // removing first element of previous
    // window and adding last element of
    // current window.
    int current_sum  = sum_so_far;
    for (int i = k; i < n; i++)
    {
        current_sum = current_sum +arr[i]-arr[i-k];
        if(current_sum>sum_so_far)sum_so_far = current_sum;
    }
    return sum_so_far;
    //Time Complexity: O(n)
    //Auxiliary Space: O(1) 
}

// Driver code
int main()
{
    int arr[] = {1, 4, 2, 10, 2, 3, 1, 0, 20};
    int k = 4;
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << maxSum(arr, n, k);
    return 0;
}