class Solution{
    public int longestOnes(int[] nums, int k){
        int currentZeroes = 0, maxLength = 0, l = 0, r = 0;
        int currentLength = 0;
        while(r<nums.length){
            currentLength++;
            r++;
            while(currentZeroes>k && l<r){
                currentLength-=1;
                if(nums[l]==0)currentZeroes--;
                l++;
            }
            currentLength = Math.max(currentLength,maxLength);
        }
        return maxLength;
    }
}