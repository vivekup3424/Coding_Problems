#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
int hashValue() class Solution
{
public:
    vector<vector<int>> subsets(vector<int> &nums) // 1,2,3
    {
        int n = nums.size();
        llu total = pow(2, n);
        vector<vector<int>> ans;
        unordered_map<int, vector<int>> mp;
        for (llu i = 0; i < total; i++)
        {
            vector<int> currentSet;
            for (llu j = 0; j < n; j++)
            {
                if (i & (1 << j))
                {
                    currentSet.push_back(nums[j]);
                }
            }
            ans.push_back(currentSet);
        }
        return ans;
    }
};
int main()
{
    fast_io();
    int T;
    cin >> T;
    while (T--)
    {
    }
}