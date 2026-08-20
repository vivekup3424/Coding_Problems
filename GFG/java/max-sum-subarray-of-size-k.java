class Solution{
    public int maxSubarraySum(int[] arr, int k){
        int n = arr.length;
        int subarraySum = 0;
        for(int i = 0; i < n & i < k; i++){
            subarraySum+=arr[i];
        }
        if(n < k) return subarraySum;
    }
}