class Solution{
    public double findMaxAverage(int[] nums, int k){
        int current_sum = 0;
        for (int i = 0; i < k; i++) {
            current_sum+=nums[i];
        }
        int max_sum = current_sum;
        for (int i = k; i < nums.length; i++) {
            current_sum = current_sum + nums[i] - nums[i-k];
            max_sum = Math.max(max_sum,current_sum);
        }
        return (double)max_sum/(double)k;
    }
}