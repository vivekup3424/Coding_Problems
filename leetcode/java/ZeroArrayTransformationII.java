/**
 * You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri, vali].

Each queries[i] represents the following action on nums:

    Decrement the value at each index in the range [li, ri] in nums by at most vali.
    The amount by which each value is decremented can be chosen independently for each index.

A Zero Array is an array with all its elements equal to 0.

Return the minimum possible non-negative value of k, such that after processing the 
first k queries in sequence, nums becomes a Zero Array. If no such k exists, return -1.
 */
public class ZeroArrayTransformationII {
    public boolean isZeroArray(int[] nums, int[][] queries, int k){
        int n = nums.length;
        int[] prefix = new int[n];
        for(int i = 0; i < k; i++){
            int l = queries[i][0], r = queries[i][1], val = queries[i][2];
            prefix[l] -= val;
            if(r + 1 < n) prefix[r + 1] += val;
        }
        for(int i = 1; i < n; i++){
            prefix[i] += prefix[i-1];
        }
        for(int i = 0; i < n; i++){
            if(nums[i] + prefix[i] > 0) return false;
        }
        return true;
    }
    public int minZeroArray(int[] nums, int[][] queries) {
        //finding the lower bound
        int m = queries.length;
        int l = 0, r = m;
        int answer = -1;
        while(l <= r){
            int mid = l + (r - l) / 2;
            if(isZeroArray(nums, queries, mid)){
                answer = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return answer;
    }
}
