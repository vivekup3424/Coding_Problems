/**
 * You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed and is protected by a security system with a color code.

You are given two integer arrays nums and colors, both of length n, where nums[i] is the amount of money in the ith house and colors[i] is the color code of that house.

You cannot rob two adjacent houses if they share the same color code.

Return the maximum amount of money you can rob
 */
class Solution {
    public long rob(int[] nums, int[] colors) {
        int n = nums.length;
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        long[] dp = new long[n];
        dp[0] = nums[0];
        dp[1] = colors[0] == colors[1] ? Math.max(nums[0], nums[1]) : nums[0] + nums[1];

        for (int i = 2; i < n; i++) {
            long robCurrent = colors[i] == colors[i - 1] ? dp[i - 2] + nums[i] : dp[i - 1] + nums[i];
            dp[i] = Math.max(dp[i - 1], robCurrent);
        }

        return dp[n - 1];
    }
}