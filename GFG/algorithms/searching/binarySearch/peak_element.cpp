// find a peak element in an unsorted array
// Method 1 Use linear tranversal to find the element
// Method 2 use Divide and Conquer or use Binary Search to find the element
#include <bits/stdc++.h>
using namespace std;

int peak_element(vector<int> v)
{
    int low = 0, high = v.size() - 1, mid;
    if (v.size() == 1)
        return v[0];
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        // first case if mid is the answer
        if ((mid == 0 || v[mid - 1] < v[mid]) and (mid == v.size() - 1 || v[mid + 1] < v[mid]))
        {
            return v[mid];
        }
        else if (v[mid] > v[mid + 1])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
}

int main()
{
    int N;
    cin >> N;
    vector<int> V(N);
    for (int i = 0; i < N; i++)
    {
        cin >> V[i];
    }
    int peak = peak_element(V);
    cout << peak << "\n";
    return 0;
}