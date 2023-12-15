class Solution
{
public:
    void backTrack(vector<int> &nums, vector<int> &current, vector<vector<int>> &ans, int idx)
    {
        if (idx == nums.size())
        {
            ans.push_back(current);
            return;
        }
        current.push_back(nums[idx]);
        backTrack(nums, current, ans, idx + 1);
        current.pop_back();
        backTrack(nums, current, ans, idx + 1);
    }
    vector<vector<int>> subsets(vector<int> nums)
    {
        vector<int> current;
        vector<vector<int>> ans;
        int idx = 0;
        backTrack(nums, current, ans, idx);
        return ans;
    }
};