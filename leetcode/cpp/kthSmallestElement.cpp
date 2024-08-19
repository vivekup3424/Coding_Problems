#include <bits/stdc++.h>
using namespace std;

int kthSmallest(vector<int> &arr, int k)
{
    priority_queue<int> pq;
    for (int i = 0; i < arr.size(); i++)
    {
        pq.push(arr[i]);
        if (pq.size() > k)
        {
            pq.pop();
        }
        }
    return pq.top();
}

int main()
{
    vector<int> v = {7, 10, 4, 3, 20, 15};
    int k = 3;
    kthSmallest(v, k);
}