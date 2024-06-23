package main

import "fmt"

func sortColors(nums []int) {
	n := len(nums)
	for i, j, k := -1, n, 0; k < j; {
		if nums[k] == 0 {
			i++
			nums[i], nums[k] = nums[k], nums[i]
			k++
		} else if nums[k] == 2 {
			j--
			nums[j], nums[k] = nums[k], nums[j]
		} else if nums[k] == 1 {
			k++
		}
	}
	fmt.Println(nums)
}
