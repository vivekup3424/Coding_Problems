//Method 1
//Recursion
class Solution {
public:
    int helper(vector<int> &nums, int target, int n)
    {
        //n is the length of the vector
        if(n==0)
        {
            return target == 0? 1: 0;
        }
        //adding athe last or subtracting it
        return (helper(nums, target-nums[n-1],n-1)+ helper(nums, target+nums[n-1],n-1));
    }
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        return helper(nums,target,n);
    }
    //Time Complexity = O(2^n)
    //Space Complexity = O(n)
};

//Method 2
//DP - Bottom Up

