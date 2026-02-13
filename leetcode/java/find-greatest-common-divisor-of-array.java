class Solution{
    private int recurse(int a, int b){
        if(b==0){
            return a;
        }
        return recurse(b, a % b);
    }
    public int findGCD(int[] nums){
        int mini = Integer.MAX_VALUE, maxi = Integer.MIN_VALUE;
        for (int i = 0; i < nums.length; i++) {
           mini = Math.min(nums[i], mini);
           maxi = Math.max(nums[i], maxi);
        }
        return recurse(maxi, mini);
    }
}