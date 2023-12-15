#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maxDigit(int n)
    {
        int mD = -1;
        while (n > 0)
        {
            mD = max(mD, n % 10);
            n = n / 10;
        }
        return mD;
    }
    int maxSum(vector<int> &nums)
    {
        unordered_map<int, vector<int>> mp;
        for (int num : nums)
        {
            int mD = maxDigit(num);
            mp[mD].push_back(num);
        }
        int maxTotal = -1;
        for (auto it : mp)
        {
            if (it.second.size() >= 2)
            {
                int n = it.second.size();
                sort(it.second.begin(), it.second.end());
                maxTotal = max(maxTotal, it.second[n - 1] + it.second[n - 2]);
            }
        }
        return maxTotal;
    }
};
int main()
{
    vector<int> v = {84, 91, 18, 59, 27, 9, 81, 33, 17, 58};
}