class HouseRobberII {
    public int rob(int[] nums) {
        int n = nums.length;
        if (n == 1) return nums[0];
        if (n == 2) return Math.max(nums[0], nums[1]);
        return Math.max(robRange(nums, 0, n - 2), robRange(nums, 1, n - 1));
    }

    private int robRange(int[] nums, int lo, int hi) {
        int first = nums[lo], second = Math.max(nums[lo], nums[lo + 1]);
        for (int i = lo + 2; i <= hi; i++) {
            int temp = Math.max(nums[i] + first, second);
            first = second;
            second = temp;
        }
        return second;
    }
}
