package main

import (
	"fmt"
	"math"
)

func equalSubstring(s string, t string, maxCost int) int {
	n := len(s)
	diff := make([]int, n)
	for i := 0; i < n; i++ {
		diff[i] = int(math.Abs(float64(s[i]) - float64(t[i])))
	}
	fmt.Println(diff)
	for i := 1; i < n; i++ {
		diff[i] = diff[i] + diff[i-1]
	}
	fmt.Println(diff)
	return 3
}
