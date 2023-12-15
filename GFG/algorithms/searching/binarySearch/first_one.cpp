// find the index of first one in infinite sorted array

// Find the index of first 1 in an infinite sorted array of 0s and 1s

// this problem is combined of first occurence problem and infinete
// sorted array problem
#include <bits/stdc++.h>
using namespace std;
/*
int low = 0
int high = 1
while(key>arr[high])
{
    low = high;
    high = high*2
}*/
int first_occurence_infinte(vector<int> v, int value)
{
    int low = 0, high = 1, mid;
    int first_occurence = -1;
    while (value > v[high])
    {
        low = high;
        high = high * 2;
    }

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
int main()
{
    int N, K;
    cin >> N >> K;
    vector<int> V(N);
    for (int i = 0; i < N; i++)
    {
        cin >> V[i];
    }
    int result = first_occurence_infinte(V, K);
    cout << result << "\n";
    return 0;
}
//_aditya verma