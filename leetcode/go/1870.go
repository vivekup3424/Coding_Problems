package main

import (
	"math"
)

func calculateTime(dist []int, speed int) int {
	time := 0
	for _, v := range dist {
		if v < time {
			return -1
		}
		t := v / time
		if v%time != 0 {
			t += 1
		}
		time += t
	}
	return time
}
func minSpeedOnTime(dist []int, hour float64) int {
	//hightest speed total distance/1 hour
	//lowest speed is 1kmph
	sum := 0
	for _, v := range dist {
		sum += v
	}
	value := int(math.Pow(2, 31) - 1)
	for l, r := 1, sum; l <= r; {
		mid = 
	}
	return value
}
