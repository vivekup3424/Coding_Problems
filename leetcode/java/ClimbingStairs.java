public class ClimbingStairs {
    public int recurse(int n){
        if(n==0 || n==1)return 1;
        else return recurse(n-1)+recurse(n-2);
    }
    public int memoized(int n, int[] memo){
        if(memo[n]!=0) return memo[n];
        else if(n==0 || n==1){
            return 1;
        }
        else{
            return memoized(n-1, memo) + memoized(n-2, memo);
        }
    }
    public int tabulate(int n){
        int[] dp = new int[n+1];
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i < n; i++) {
           dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }

    public int memoryOptimized(int n){
        int first = 1, second = 1;
        if(n == 1 || n == 0) return 1;
        for(int i = 2; i < n; i++){
            int answer = first + second;
            first = second;
            second = answer;
        }
        return second;
    }
}
