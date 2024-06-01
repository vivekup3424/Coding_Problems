package main

import "math"

func scoreOfString(s string) int {
	sum := 0
	n := len(s)
	v := []byte(s)
	for i := 1; i < n; i++ {
		sum += int(math.Abs(float64(v[i]) - float64(v[i-1])))
	}
	return sum
}
