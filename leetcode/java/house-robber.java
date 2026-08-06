/*
 * 198. House Robber
 * https://leetcode.com/problems/house-robber/
 *
 * You are a professional robber planning to rob houses along a street. Each
 * house has a certain amount of money stashed, the only constraint stopping
 * you from robbing each of them is that adjacent houses have security
 * systems connected and it will automatically contact the police if two
 * adjacent houses were broken into on the same night.
 *
 * Given an integer array nums representing the amount of money of each
 * house, return the maximum amount of money you can rob tonight without
 * alerting the police.
 *
 * Example 1:
 *   Input:  nums = [1,2,3,1]
 *   Output: 4
 *   Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
 *     Total amount you can rob = 1 + 3 = 4.
 *
 * Example 2:
 *   Input:  nums = [2,7,9,3,1]
 *   Output: 12
 *   Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob
 *     house 5 (money = 1). Total amount you can rob = 2 + 9 + 1 = 12.
 *
 * Constraints:
 *   - 1 <= nums.length <= 100
 *   - 0 <= nums[i] <= 400
 */
class Solution {
    private int recurse(int[] nums, int i){
        if(i < 0) return 0;
        if(i==0 || i == 1) return nums[i];
        return Math.max(nums[i] + recurse(nums,i-2), recurse(nums,i-1));
    }
    public int rob(int[] nums) {
        int n = nums.length;
        int[] dp = new int[n];
        for(int i = 0; i < n; i++){
            if(i==0) dp[i] = nums[i];
            else if(i==1) dp[i] = Math.max(nums[i],nums[i-1]);
            else{
                dp[i] = Math.max(nums[i]+dp[i-2], dp[i-1]);
            }
        }
        return dp[n-1];
    }

}
