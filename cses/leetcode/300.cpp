#include <bits/stdc++.h>
using namespace std;

class Solution1 {
public:
    //recursive solution
    int recurse(vector<int> &nums, int current, int prev){
        if(current >= nums.size())return 0;
        int first = 0, second = 0;
        //choosing the ith element
        if(prev == -1 || nums[prev] < nums[current]){ //condtion for choosing the ith element
            first = 1 + recurse(nums, current+1, current);
        }
        //not choosing the ith element
        second = recurse(nums, current+1, prev);
        return max(first, second);
    }
    int lengthOfLIS_recursive(vector<int>& nums) {
            int idx = 0;
            int maxElement = 0;
            int *length = 0;
            return recurse(nums, 0,-1);
    }

    int longest(vector<int> &nums, vector<vector<int>> &memo, int prev, int current){
        if(current == nums.size())return 0;
        else if(prev != -1 and memo[prev][current]!=-1)return memo[prev][current];
        int first = 0, second = 0;
        if(prev == -1 or nums[prev]< nums[current]){
            first = 1 + longest(nums, memo, current, current + 1);
        }
        //not choosing the ith element
        second = longest(nums, memo, prev, current + 1);
        if(prev != -1){
            return memo[prev][current] = max(first, second);
        }
        else return max(first, second);
    }
    int lengthOfLIS_memoized(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        return longest(nums,memo, -1, 0);
    }

    //dp solution 
    int lengthOfLIS(vector<int> &nums){
        int n = nums.size();
        vector<int> dp(n, 1);
        for(int i = 0; i < n;i++){
            for(int j = 0; i > j; j++){
                if(nums[i] > nums[j] and (dp[i] < dp[j] + 1)){
                    dp[i] = dp[j] + 1;
                }
            }
        }
        return max_element(dp.begin(), dp.end());
    }
};