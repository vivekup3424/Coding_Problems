/**
 * Partition Equal Subset Sum
 * 
 * Problem: Given an integer array nums, return true if you can partition the array 
 * into two subsets such that the sum of elements in both subsets is equal.
 * 
 * Examples:
 * 1. Input: nums = [1,5,11,5]
 *    Output: true
 *    Explanation: Can be partitioned as [1,5,5] and [11].
 *    
 * 2. Input: nums = [1,2,3,5]
 *    Output: false
 *    Explanation: Cannot be partitioned into equal sum subsets.
 * 
 * Constraints:
 * - 1 <= nums.length <= 200
 * - 1 <= nums[i] <= 100
 */

#include <bits/stdc++.h>
#include <numeric>
using namespace std;

class Solution {
public:
    bool canPartition(std::vector<int>& nums) {
        int total_sum = accumulate(nums.begin(), nums.end(),0);
        if(total_sum%2==1){
            return false;
        }
        int n = nums.size();
        int half = (total_sum)/2;
        bool dp[n+1][half+1];
        for(int i = 0; i < n+1; i++){
            for(int j = 0; j < half+1; j++){
                if(i==0){
                    //no element to choose
                    dp[i][j] = false;
                }
                else if(j==0){
                    dp[i][j] = true;
                }else if(nums[i-1]<j){
                    dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]];
                }
                else{
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[n][half];
    }
};
