import java.util.Arrays;

class Solution{
    public boolean isGood(int[] nums) {
        int n = nums.length;
        int[] baseArr = new int[n]; //[1...m-1,m,m] => m+1 = n => m = n - 1
        for(int i = 0; i < n-1; i++){ //n-2 = m-1 => baseArr[m-1] = m-1+1
            baseArr[i] = i+1;
        }
        baseArr[n-1] = n-1;
        Arrays.sort(nums);
        for(int i = 0; i < n; i++){
            if(baseArr[i] != nums[i]) return false;
        }
        return true;
    }
}