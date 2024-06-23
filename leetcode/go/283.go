package main

func moveZeroes(nums []int) {
	j := 0
	n := len(nums)
	for i := 0; i < n; i++ {
		if nums[i] != 0 {
			temp := nums[i]
			nums[i] = nums[j]
			nums[j] = temp
			j++
		}
	}
}
