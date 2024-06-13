/*Given an array and a positive integer k, find the 
first negative integer for each window(contiguous subarray) of 
size k. If a window does not contain a negative integer, 
then print 0 for that window.*/

// C++ implementation to find the first negative
// integer in every window of size k
#include <iostream>
#include <deque>
using namespace std;

// function to find the first negative
// integer in every window of size k
void printFirstNegativeInteger(int arr[], int n, int k)
{
    deque<int> dq;
    // flag to check whether window contains
    // a negative integer or not
    bool flag;

    for (int i = 0; i < k; i++) //if getting the negatives of first kth subarray
    {
        if(arr[i]<0)dq.push_back(arr[i]);
    }
    
    if(!dq.empty()) //if dq is not empty
    {
        cout<<dq.front()<<"\t"; //printing the first negative element of first subarray
    }
    else
    {
        cout<<0<<"\t";
    }
    for (int i = k; i < n; i++)
    {
        if(!dq.empty())
        {
            //if previous subarray first number is equal to its first negative number
            //then pop that element from the dq//if previous subarray first number is equal to its first negative number
        //then pop that element from the dq
        if(arr[i-k]==dq.front())dq.pop_front();
        }
        if(arr[i]<0)dq.push_back(arr[i]); //for next subarray including the success negative integer

        if(dq.empty())cout<<0<<"\t";
        else cout<<dq.front()<<"\t";
    }
    return ;
    /*
    Time Complexity: O(n) 

    Auxiliary Space: O(k)
    */
}

// Driver program to test above functions
int main()
{
    int arr[] = {12, -1, -7, 8, -15, 30, 16, 28};
    int n = sizeof(arr)/sizeof(arr[0]);
    int k = 3;
    printFirstNegativeInteger(arr, n, k);
    return 0;
}