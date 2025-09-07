class Solution{
    private boolean areAllElementsEqual(int[] nums){
        if(nums.length<2){
            return true;
        }
        int firstElement = nums[0];
        for (int i = 1; i < nums.length; i++) {
            if(nums[i]!=firstElement){
                return false;
            }
        }
        return true;
    }
    public int minOperations(int[] nums){
        if(areAllElementsEqual(nums)){
            return 0;
        }else{
            return 1;
        }
    }
}