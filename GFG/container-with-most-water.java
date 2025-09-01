/**
 * Given an array arr[] of non-negative integers, where each element arr[i] represents 
 * the height of the vertical lines, find the maximum amount of water that 
 * can be contained between any two lines, together with the x-axis.
 * Note: In the case of a single vertical line it will not be able to hold water.
 */

class Solution{
    public int maxWater(int[] arr){
        int n = arr.length;
        if(n < 2)return 0;
        int l = 0, r = n - 1;
        long best = 0;
        while(l < r){
            long h = Math.min(arr[l], arr[r]);
            long area = h * (r - l);
            area = Math.max(area,best);
            if(arr[l]<arr[r]){
                l++;
            }else {
                r--;
            }
        }
        return (int)best;
    }
}