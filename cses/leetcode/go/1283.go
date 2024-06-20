package main

import (
	"fmt"
	"math"
	"sort"
)

type Ints []int

func (a Ints) Len() int           { return len(a) }
func (a Ints) Swap(i, j int)      { a[i], a[j] = a[j], a[i] }
func (a Ints) Less(i, j int) bool { return a[i] < a[j] }
func calculateValue(nums []int, speed int) int {
	var total int
	for _, v := range nums {
		total += int(math.Ceil(float64(v) / float64(speed)))
	}
	fmt.Printf("Total = %v, for speed = %v\n", total, speed)
	return total
}
func smallestDivisor(nums []int, threshold int) int {
	sort.Ints(nums)
	fmt.Println(nums)
	l, r := 0, nums[len(nums)-1]
	ans := r
	for l <= r {
		mid := (l + r) >> 1 //bitwise right shift(divides by 2)
		time := calculateValue(nums, mid)
		if time <= threshold {
			ans = mid
			r = mid - 1
		} else {
			l = mid + 1
		}
	}
	fmt.Println("Ans =", ans)
	return ans
}
