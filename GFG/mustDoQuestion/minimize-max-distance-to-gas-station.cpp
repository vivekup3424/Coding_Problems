#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    double findSmallesMaxDist(vector<int> &stations, int k)
    {
        priority_queue<double, vector<double>> maxHeap;
        int n = stations.size();
        for (int i = 1; i < n; i++)
        {
            double dist =
                (double)stations[i] - (double)stations[i - 1];
            maxHeap.push(dist);
        }
        while (k--)
        {
            double d = maxHeap.top();
            maxHeap.pop();
            d = d / 2;
            maxHeap.push(d);
            maxHeap.push(d);
        }
        // cout << maxHeap.top() << endl;
        double d = maxHeap.top();
        printf("%0.2f", d);
        return d;
    }
};

int main()
{
    vector<int> v = {3, 6, 12, 19, 33, 44, 67, 72, 89, 95};
    int k = 2;
    Solution A;
    int m = A.findSmallesMaxDist(v, k);
}