
#include <bits/stdc++.h>
using namespace std;
class Solution1
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        vector<int> c(n - 1);
        for (int i = 0; i < n - 1; i++)
        {
            c[i] = (prices[i + 1] - prices[i]);
        }
        int sum = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if (c[i] > 0)
                sum += c[i];
        }
        return sum;
    }
    // Time=O(n)
    // Space=O(n)
};
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        int sum = 0;
        for (int i = 0; i < n - 1; i++)
        {
            int diff = (prices[i + 1] - prices[i]);
            if (diff > 0)
                sum += diff;
        }
        return sum;
    }
};

int main()
{
}