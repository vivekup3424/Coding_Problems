class Solution{
    public boolean increasingTriplet(int[] nums) {
        int indexOfMini = 0, indexOfMaxi = nums.length-1;
        int l = 0, r = nums.length-1;
        while (l<r) {
            if(nums[l]< nums[indexOfMini]){
                indexOfMini = l;
            }
            if(nums[r]>nums[indexOfMaxi]){
                indexOfMaxi = r;
            }
        }
    }
}