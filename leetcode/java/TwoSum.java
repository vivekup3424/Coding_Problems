import java.util.HashMap;
import java.util.Map;

class Solution {
    public int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> indexOf = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if (indexOf.containsKey(complement)) {
                return new int[] { indexOf.get(complement), i };
            }
            indexOf.put(nums[i], i);
        }
        return new int[] {};
    }
    public int[] Naive(int[] nums, int target){
        int n = nums.length;
        for(int i = 0 ; i < n; i++){
            for(int j = i+1; j < n; j++){
                if(nums[i]+nums[j] == target){
                    return new int[] {i,j};
                }
            }
        }
        return new int[]{};
    }
}
