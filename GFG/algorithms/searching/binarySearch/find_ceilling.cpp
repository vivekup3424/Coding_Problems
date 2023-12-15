// Given a sorted array and a value x, the ceiling of x is
// the smallest element in an array greater than or equal to x,
// and the floor is the greatest element smaller than or equal to x.
// Assume that the array is sorted in non - decreasing order.
// Write efficient functions to find the floor and ceiling of x.
//  Method 1 Linear Searching
//  Method 2 Binary Searching
#include <bits/stdc++.h>
using namespace std;
int find_ceilling(vector<int> v, int k)
{
    int low = 0, high = v.size() - 1, mid;
    int result = -1;
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        if (v[mid] == k)
        {
            result = k;
            break;
        }
        else if (v[mid] > k)
        {
            result = v[mid];
            high = high - 1;
        }
        else if (v[mid] < k)
        {
            low = mid + 1;
        }
    }
    return result;
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
    int result = find_ceilling(V, K);
    cout << result << "\n";
    return 0;
}