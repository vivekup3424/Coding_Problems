#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        vector<int> diff;
        for (int i = 1; i < prices.size(); i++)
        {
            diff.push_back(prices[i] - prices[i - 1]);
        }
        // print the vector
        for (auto it : diff)
        {
            cout << it << " ";
        }
        cout << endl;
        // making use of a heap
        priority_queue<int, vector<int>> maxHeap;
        int current_sum = 0;
        for (size_t i = 0; i < diff.size(); i++)
        {
            if (diff[i] < 0)
            {
                current_sum = 0;
            }
            else
            {
                current_sum += diff[i];
            }
            maxHeap.push(current_sum);
        }
        cout << "printing the maxHeap" << endl;
        int sum = 0;
        while (maxHeap.size() > 0)
        {
            if (k > 0)
            {
                sum += maxHeap.top();
            }
            cout << maxHeap.top() << " ";
            cout << endl;
        }
    }
};
int main()
{
    vector<int> prices
}