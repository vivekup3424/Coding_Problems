public class MaximumSumProblem {
    int maxSum(int n){
        if(n == 0) return 0;
        return Math.max(n, maxSum(n/2) + maxSum(n/3) + maxSum(n/4));
    }
    int dp(int n){
        int[] answer = new int[n+1];
        for(int i = 1; i <= n; i++){
            answer[i] = Math.max(i,
                answer[i/2] + answer[i/3] + answer[i/4]
            );
        }
        return answer[n];
    }
}
