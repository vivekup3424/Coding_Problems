public class ZeroArrayTransformationI {
    public boolean isZeroArray(int[] nums, int[][] queries) {
        int n = nums.length;
        int[] prefix = new int[n];
        for(int[] query : queries){
            int l = query[0], r = query[1];
            prefix[l] -= 1;
            if(r+1 < n) prefix[r+1] += 1;
        }
        for(int i = 1; i < n; i++){
            prefix[i]+=prefix[i-1];
        }
        for(int i = 0; i < n; i++){
            if(nums[i] + prefix[i] > 0) return false;
        }
        return true;
    }
}