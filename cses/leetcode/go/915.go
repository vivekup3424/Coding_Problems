package main

func partitionDisjoint(nums []int) int {
	//left to right array holding the smallest value
	//in the suffix at each index
	n := len(nums)
	left :=make([]int,n)
	for(i := n-1; i >=0; i--){
		if i == n-1{
			left[i] = nums[i];
		}
		else {
			left[i] = math
		}
	}
}
