class Solution {
    public int longestSubarray(int[] nums) {
        int maxLength = 0;
        //find the maxElement
        int maxElement = nums[0];
        for (int i = 0; i < nums.length; i++) {
            maxElement = Math.max(maxElement,nums[i]);
        }
        //find the length of continuous segment containing the maxElement
        int currentLength = 0;
        int l = 0, r = 0;
        while(r<nums.length){
            if(nums[r]!=maxElement){
                currentLength = 0;
            }
            else{
                currentLength+=1;
            }
            maxLength = Math.max(maxLength,currentLength);
        }
        return maxLength;
    }
}