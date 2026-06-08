public class MinCostClimbingStairs {
    public int minCostClimbingStairs(int[] cost){
        int n = cost.length;
        int[] dp = new int[n+1];
        dp[0] = 0;
        for (int i = 1; i < dp.length; i++) {
            if(i==1 || i == 2) dp[i] = cost[i-1];
            else{
                dp[i] = Math.min(dp[i-1],dp[i-2]) + cost[i-1];
            }
        }
        return Math.min(dp[n],dp[n-1]);
    }
}