package main

func searchInsert(nums []int, target int) int {
	l, r := 0, len(nums)-1
	if nums[len(nums)-1] < target {
		return len(nums)
	}
	mid := (l + r) / 2
	for l < r {
		if nums[mid] == target {
			return target
		} else if nums[mid] > target {
			r = mid - 1
		} else {
			l = mid + 1
		}
	}
	return mid
}
