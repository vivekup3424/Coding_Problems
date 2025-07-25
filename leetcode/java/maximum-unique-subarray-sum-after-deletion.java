import java.util.*;

class Solution {
    public int maxSum(int[] nums) {
        Set<Integer> set = new HashSet<Integer>();
        Arrays.sort(nums);
        if(nums[nums.length-1]<0){
            return nums[nums.length-1];
        }
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] > 0) {
                set.add(nums[i]);
            }
        }
        Integer sum = 0;
        for (Integer num : set) {
            sum += num;
        }
        return sum;
    }
}