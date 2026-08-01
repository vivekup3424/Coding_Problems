/*
 * 18. 4Sum
 * https://leetcode.com/problems/4sum/
 *
 * Given an array nums of n integers, return an array of all the unique
 * quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
 *   - 0 <= a, b, c, d < n
 *   - a, b, c, and d are distinct.
 *   - nums[a] + nums[b] + nums[c] + nums[d] == target
 *
 * You may return the answer in any order.
 *
 * Example 1:
 *   Input:  nums = [1,0,-1,0,-2,2], target = 0
 *   Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
 *
 * Example 2:
 *   Input:  nums = [2,2,2,2,2], target = 8
 *   Output: [[2,2,2,2]]
 *
 * Constraints:
 *   - 1 <= nums.length <= 200
 *   - -10^9 <= nums[i] <= 10^9
 *   - -10^9 <= target <= 10^9
 */

import java.util.*;

class Solution {
    public List<List<Integer>> fourSum(int[] nums, int target) {
        Arrays.sort(nums);
        List<List<Integer>> answer = new ArrayList<>();
        int n = nums.length;
        for(int i = 0; i < nums.length; i++){
            if(i > 0 && nums[i]==nums[i-1]) continue;

            for(int j = i+1; j < nums.length; j++){
                if(j > i+1 && nums[j]==nums[j-1]) continue;

                int k = j+1, l = n-1;
                while(k < l){
                    long sum = (long) nums[i] + nums[j] + nums[k] + nums[l];
                    if(sum == target){
                        answer.add(Arrays.asList(nums[i], nums[j], nums[k], nums[l]));
                        k++;
                        l--;
                        while(k < l && nums[k]==nums[k-1]) k++;
                        while(k < l && nums[l]==nums[l+1]) l--;
                    }
                    else if(sum > target){
                        l--;
                    }
                    else{
                        k++;
                    }
                }
            }
        }
        return answer;
    }
}
