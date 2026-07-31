/*
 * 16. 3Sum Closest
 * https://leetcode.com/problems/3sum-closest/
 *
 * Given an integer array nums of length n and an integer target, find
 * three integers at distinct indices in nums such that the sum is closest to target.
 *
 * Return the sum of the three integers.
 *
 * You may assume that each input would have exactly one solution.
 *
 * Example 1:
 *   Input:  nums = [-1,2,1,-4], target = 1
 *   Output: 2
 *   Explanation: The sum that is closest to the target is 2.
 *     (-1 + 2 + 1 = 2).
 *
 * Example 2:
 *   Input:  nums = [0,0,0], target = 1
 *   Output: 0
 *   Explanation: The sum that is closest to the target is 0.
 *     (0 + 0 + 0 = 0).
 *
 * Constraints:
 *   - 3 <= nums.length <= 500
 *   - -1000 <= nums[i] <= 1000
 *   - -10^4 <= target <= 10^4
 */

import java.util.Arrays;

class Solution {
    public int threeSumClosest(int[] nums, int target) {
        int n = nums.length;
        int diff = Integer.MAX_VALUE, ans = -1;
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                for(int k = j + 1; k < n; k++){
                    int sum = nums[i] + nums[j] + nums[k];
                    if(Math.abs(sum-target)<diff){
                        diff = Math.abs(sum-target);
                        ans = sum;
                    }
                }
            }
        }
        return ans;
    }

    public int betterThreeSumClosest(int[] nums, int target){
        Arrays.sort(nums);
        int diff = Integer.MAX_VALUE, ans = -1;
        int n = nums.length;
        for(int i = 0; i < n; i++){
            int j = i + 1, k = n-1;
            while(j < k){
                int sum = nums[i] + nums[j] + nums[k];
                if(sum > target){
                    k--;
                }
                else if(sum < target){
                    j++;
                }else{
                    return sum;
                }
                
                //re-adjust the diff
                int new_diff = Math.abs(target - sum);
                if(new_diff < diff){
                    diff = new_diff;
                    ans = sum;
                }
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        System.out.println(sol.threeSumClosest(new int[]{-1,2,1,-4}, 1)); // expected 2
        System.out.println(sol.threeSumClosest(new int[]{0,0,0}, 1));     // expected 0
    }
}
