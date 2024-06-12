#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    int maxReward(vector<int> &r, int idx, int sum, int &maxSum)
    {
        maxSum = max(maxSum, sum);
        if (idx == r.size())
        {
            return maxSum;
        }
        if (sum < r[idx])
        {
            // choose the ith elemetn
            return max(
                maxReward(r, idx + 1, sum + r[idx], maxSum),
                maxReward(r, idx + 1, sum, maxSum));
        }
        else
        {
            // cant choose the ith element
            return maxReward(r, idx + 1, sum, maxSum);
        }
    }
    int maxTotalReward(vector<int> &r)
    {
        sort(r.begin(), r.end());
        int n = r.size();
        int maxSum = 0, sum = 0;
        return maxReward(r, 0, sum, maxSum);
        int totalSum = 0;
        for (auto i : r)
        {
            totalSum +=
        }
    }
};
int main()
{
    Solution sol;
    vector<int> rewards = {2, 1, 4, 3};
    cout << sol.maxTotalReward(rewards) << endl;
    return 0;
}