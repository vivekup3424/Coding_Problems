// Given a sorted array of numbers, find if a given number
//‘key’ is present in the array. Though we know that the
// array is sorted, we don’t know if it’s sorted in ascending
// or descending order. .
#include <bits/stdc++.h>
using namespace std;
int BS_reverse_array(vector<int> V, int value)
{
    int low = V.size() - 1;
    int high = 0;
    int mid; // prevents overflow
    bool result = false;
    while (low >= high)
    {
        mid = low + (high - low) / 2; // prevents overflow
        if (V[mid] == value)
        {
            result = true;
            return mid; // returns index, not position
        }
        if (value > V[mid])
        {
            low = mid - 1;
        }
        else
        {
            high = mid + 1;
        }
    }
    if (!result)
        return -1;
}
int binarySearch(vector<int> v, int To_Find)
{
    int lo = 0, hi = v.size() - 1;
    int mid;
    // This below check covers all cases , so need to check
    // for mid=lo-(hi-lo)/2
    while (hi - lo > 1)
    {
        int mid = (hi + lo) / 2;
        if (v[mid] < To_Find)
        {
            lo = mid + 1;
        }
        else
        {
            hi = mid;
        }
    }
    if (v[lo] == To_Find)
    {
        cout << "Found"
             << " At Index " << lo << endl;
    }
    else if (v[hi] == To_Find)
    {
        cout << "Found"
             << " At Index " << hi << endl;
    }
    else
    {
        cout << "Not Found" << endl;
    }
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
    bool choice;
    choice = (V[0] < V[N - 1]) ? true : false;
    switch (choice)
    {
    case true:
        binarySearch(V, K);
        break;
    case false:
        cout << BS_reverse_array(V, K) << "\n";
        break;
    default:
        break;
    }
    return 0;
}