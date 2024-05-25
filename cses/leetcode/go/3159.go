package main

import "fmt"

// Simple Hashmap operation
func occurrencesOfElement(nums []int, queries []int, x int) []int {
	var occurences []int
	for idx, val := range nums {
		if val == x {
			occurences = append(occurences, idx)
		}
	}
	n := len(occurences)
	length := len(queries)
	answer := make([]int, length)
	for idx, val := range queries {
		if val > n {

			answer[idx] = -1
		} else {
			answer[idx] = occurences[val-1]
		}
	}
	fmt.Println(answer)
	return answer
}
