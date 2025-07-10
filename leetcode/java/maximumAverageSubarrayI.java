public class maximumAverageSubarrayI {
    public double findMaxAverage(int[] nums, int k) {
        double sum = 0;
        int total_length = nums.length;
        for(int i =0;i < k; i++){
            sum += nums[i];
        }
        double currentAvg = sum/k;
        double maxAvgSoFar = currentAvg;
        for(int i =k; i < nums.length; i++){
            
        }
        return 1.0;
    } 
}
