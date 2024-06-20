package main

import "math"

// going for the fucking naive approach
func minDaysNaive(bloomDay []int, m int, k int) int {
	n := len(bloomDay)
	numFlowersRequired := m * k
	if numFlowersRequired > n {
		return -1
	}
	visited := make([]bool, n)
	println("Visited=", visited)
	minValue := int(math.Inf(1))
	minIdx := -1 //index of the starting element of minWindow
	for i := 0; i < n-m; i++ {
		//get a minWindow of length m
		value := 0
		var breakOccured = false
		for d := 0; d < m; d++ {
			if visited[i+d] == true {
				breakOccured = true
				break
			} else {
				value += bloomDay[i+d]
			}
		}
		if value < minValue {
			minValue = value
			minIdx = i
		}
	}
	return 0
}

func minDays(bloomDay []int, m, k int) int {

}
