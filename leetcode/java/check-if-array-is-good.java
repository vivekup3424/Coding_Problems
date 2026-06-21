import java.util.Arrays;

class Solution{
    public boolean isGood(int[] nums) {
        int n = nums.length;
        int[] baseArr = new int[n]; //[1...m-1,m,m] => m+1 = n => m = n -1
        for(int i = 0; i < n-1; i++){
            baseArr[i] = i+1;
        }
        baseArr[n-1] = n;

        Arrays.sort(nums);
        return true;
    }
}