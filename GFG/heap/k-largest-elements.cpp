#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> KLargestElement(int arr[], int n, int k)
{
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int i = 0; i < n; i++)
    {
        minHeap.push(arr[i]);
        if (minHeap.size() == k)
        {
            minHeap.pop(); // logn operation
        }
    }
    vector<int> ans;
    while (minHeap.size() > 0)
    {
        /* code */
        ans.push_back(minHeap.top());
        minHeap.pop();
    }
    reverse(ans.begin(), ans.end());
    return ans;
}