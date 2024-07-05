package main

import (
	"fmt"
	"sort"
)

func main() {
	var n int
	fmt.Scan(&n)
	nums := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&nums[i])
	}
	sort.Slice(nums, func(i, j int) bool {
		return nums[i] > nums[j]
	})
	sum := 0
	for i := 0; i < n; i += 2 {
		sum += nums[i]
	}
	fmt.Println(sum)
}
