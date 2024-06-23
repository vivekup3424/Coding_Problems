package main

import (
	"math"
)

func isBadVersion(n int) bool {
	return false
}
func firstBadVersion(n int) int {
    value := int(math.Pow(2,31) - 1) 
	for l, r := 0, n; l <= r; {
		mid := (l + r)/2
		if isBadVersion(mid) == true {
			value = min(value, mid)
			r = mid - 1
		} else {
			l = mid + 1
		}
	}
	return value
    //since all the testcases have passed, but I am getting
    //TLE so I need to see how can I get optimize the
    //time-complexity
}
