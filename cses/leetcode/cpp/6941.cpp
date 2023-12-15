class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int count[3] = {0};
        for(int i = 0; i < nums.size(); i++){
            count[nums[i]-1]++;
        }
        int num_ops = count[1] + count[2];
        num_ops += nums.size() - count[0] - count[1] - count[2];
        return num_ops;
    }
};