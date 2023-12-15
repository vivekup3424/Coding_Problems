/*Given an array and an integer K, find the maximum for 
each and every contiguous subarray of size K.*/

#include <iostream>
#include <deque>
using namespace std;

//dequeue and sliding window method for finding maximum 
//for each subarray

//n is size of array, k is size of subarray
void printMax(int arr[],int N,int K)
{
    deque<int> Qi(K); //K-length deque
    // Create a Double Ended Queue,
    // Qi that will store indexes
    // of array elements
    // The queue will store indexes
    // of useful elements in every
    // window and it will
    // maintain decreasing order of
    // values from front to rear in Qi, i.e.,
    // arr[Qi.front[]] to arr[Qi.rear()]
    // are sorted in decreasing order

    /*Process first k (or first window)
    elements of array*/
    int i;
    for ( i = 0; i < K; i++)
    {
        // For every element, the previous
        // smaller elements are useless so
        // remove them from Qi
        while ((!Qi.empty())&& arr[i]>=arr[Qi.back()])
        {
            //Remove from rear
            Qi.pop_back();

            //Add new element to the rear
            Qi.push_back(i);
        }
    }

    // Process rest of the elements,
    // i.e., from arr[k] to arr[n-1]
    for ( ; i < N; i++)
    {
        // The element at the front of
        // the queue is the largest element of
        // previous window, so print it
        cout << arr[Qi.front()] << " ";

        // Remove the elements which
        // are out of this window
        while((!Qi.empty()) && Qi.front()<=i-K)
        {
            // Remove from front of queue
            Qi.pop_front();
        }

        // Remove all elements
        // smaller than the currently
        // being added element (remove
        // useless elements)
        while ((!Qi.empty()) && arr[i] >= arr[Qi.back()])
            Qi.pop_back();
 
        // Add current element at the rear of Qi
        Qi.push_back(i);
    }
 
    // Print the maximum element
    // of last window
    cout << arr[Qi.front()];
}