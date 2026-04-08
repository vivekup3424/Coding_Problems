public class HouseRobber {
    //robbing from an array of houses
    public int recurse(int idx, int[] nums){
        if(idx == 0) return nums[0];
        if(idx == 1) return Math.max(nums[1],nums[0]);
        return Math.max(nums[idx] + recurse(idx-2, nums), recurse(idx-1, nums));
    }
    public int memo(int idx, int[] nums, int[] memo){
        if(memo[idx] != -1) return memo[idx];
        else if(idx == 0) return nums[0];
        else if(idx == 1) return Math.max(nums[1], nums[0]);
        else{
            memo[idx] = Math.max(nums[idx] + memo(idx-2, nums, memo), memo(idx-1, nums, memo));
            return memo[idx];
        }
    }
    public int tabulate(int[] nums){
        int n = nums.length;
        int[] dp = new int[n];
        dp[0] = nums[0];
        dp[1] = Math.max(nums[0], nums[1]);
        for(int i = 2; i < n; i++){
            dp[i] = Math.max(nums[i] + dp[i-2], dp[i-1]);
        }
        return dp[n-1];
    }
    //I am thinking if this can be memory optimized
    public int memoryOptimized(int[] nums){
        if(nums.length == 0)return nums[0];
        else if(nums.length == 1) return Math.max(nums[0] , nums[1]);
        int first = nums[0], second = nums[1];
        return -100;
    }
    
}
