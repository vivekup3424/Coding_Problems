package main

import "fmt"

func mySqrt(x int) int {
	value := -1
	for l, r := 0, x; l <= r; {
		mid := (l + r) / 2
		if mid*mid == x {
			value = mid
			break
		} else if mid*mid < x {
			value = max(value, mid)
			l = mid + 1
		} else {
			r = mid - 1
		}
	}
	fmt.Println(value)
	return value
}
