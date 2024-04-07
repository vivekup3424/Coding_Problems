package main

func check(nums []int) bool {
	count := 0
	for idx, ele := range nums {
		if idx+1 < len(nums) && ele > nums[idx+1] {
			if ele >= nums[len(nums)-1] {
				count++
			} else {
				return false
			}
		}
	}
	if count <= 1 {
		return true
	}
	return false
}
