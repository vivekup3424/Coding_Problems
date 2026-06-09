class HouseRobberII {
    public int rob(int[] nums){
        int n = nums.length;
        if(n == 1) return nums[0];
        else if(n==2) return Math.max(nums[1], nums[0]);
        int first = nums[0], second = nums[1];
        for (int i = 2; i < n; i++) {
            int temp = Math.max(nums[i] + first, second);
        }
    }
}
