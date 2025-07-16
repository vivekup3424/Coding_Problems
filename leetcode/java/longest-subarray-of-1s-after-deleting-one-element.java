class Solution {
    public int longestSubarray(int[] nums) {
        int left = 0, zeroes = 0, maxLen = 0;
        for (int right = 0; right < nums.length; right++) {
            if (nums[right] == 0) {
                zeroes++;
            }
            while (zeroes > 1) {
                if (nums[left] == 0) {
                    zeroes--;
                }
                left++;
            }
            maxLen = Math.max(maxLen, right-left+1);
        }
        return maxLen-1;
    }
}