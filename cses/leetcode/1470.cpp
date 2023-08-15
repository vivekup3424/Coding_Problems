class Solution
{
public:
    vector<int> shuffle(vector<int> &nums, int n)
    {
        vector<int> num;
        int i = 0, j = n; //two pointer approach
        while(i<n)
        {
            num.push_back(nums[i++]);
            num.push_back(nums[j++]);
        }
        return num;
    }
};
