/**
 * You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri, vali].

Each queries[i] represents the following action on nums:

    Decrement the value at each index in the range [li, ri] in nums by at most vali.
    The amount by which each value is decremented can be chosen independently for each index.

A Zero Array is an array with all its elements equal to 0.

Return the minimum possible non-negative value of k, such that after processing the first k queries in sequence, nums becomes a Zero Array. If no such k exists, return -1.
 */
public class ZeroArrayTransformationII {
    public boolean isZeroArray(int[] nums, int[][] queries, int k){
        int n = nums.length;
        int[] prefix = new int[n];
        for(int[] query : queries){
            int l = query[0], r = query[1], val = query[2];
            prefix[l]-=val;
            if(r+1 < n) prefix[r+1]+=val;
        }
        for(int i = 1; i < n; i++){
            prefix[i]+=prefix[i-1];
        }
        for(int i = 0; i < n; i++){
            if(nums[i] + prefix[i] > 0) return false;
        }
        return true;
    }
    public int minZeroArray(int[] nums, int[][] queries) {
        int m = queries.length, n = nums.length;
        int l = 0, r = m-1;
        while(l < r)
        
    }
}
