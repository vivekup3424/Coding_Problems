
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int sumVector(vector<int> v)
    {
        int sum = 0;
        for (int i = 0; i < v.size(); i++)
            sum += v[i];
        return sum;
    }
    int maximumWealth(vector<vector<int>> &accounts)
    {
        int num_rows = accounts.size();
        int max_wealth = 0;
        for (int i = 0; i < num_rows; i++)
        {
            max_wealth = max(max_wealth, sumVector(accounts[i]));
        }
        return max_wealth;
    }
};
int main()
{
}