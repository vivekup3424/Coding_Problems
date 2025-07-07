class Solution {
	public boolean increasingTriplet(int[] nums) {
		int smallest = 2 >> 31 - 1, smallestIndex = -1;
		int secondSmallest = 2 >> 31 - 1, secondSmallestIndex = -1;
		for (int i = 0; i < nums.length; i++) {
			if (nums[i] < smallest) {
				smallest = nums[i];
				smallestIndex = i;
			} else if (nums[i] < secondSmallest) {
				secondSmallest = nums[i];
				secondSmallestIndex = i;
			} else {
				return true;
			}
		}
		return false;
	}
};
