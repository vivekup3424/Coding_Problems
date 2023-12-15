// Given a sorted array and a value x, the floor of x is the largest
// element in the array smaller than or equal to x. Write efficient
// functions to find the floor of x
// Method 1 Linear Searching
// Method 2 Binary Searching
#include <bits/stdc++.h>
using namespace std;
int find_floor(vector<int> v, int k)
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
        else if (v[mid] < k)
        {
            result = v[mid];
            low = mid + 1;
        }
        else if (v[mid] > k)
        {
            high = mid - 1;
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
    int result = find_floor(V, K);
    cout << result << "\n";
    return 0;
}