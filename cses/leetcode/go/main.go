package main

import "fmt"

func main() {
	// Test cases
	intervals := [][]int{{1, 3}, {6, 9}}
	newInterval := []int{2, 5}
	fmt.Println("Before insertion:", intervals)
	fmt.Println("New interval:", newInterval)
	fmt.Println("After insertion:", insert(intervals, newInterval))

	intervals = [][]int{{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}}
	newInterval = []int{4, 8}
	fmt.Println("Before insertion:", intervals)
	fmt.Println("New interval:", newInterval)
	fmt.Println("After insertion:", insert(intervals, newInterval))

	intervals = [][]int{}
	newInterval = []int{5, 7}
	fmt.Println("Before insertion:", intervals)
	fmt.Println("New interval:", newInterval)
	fmt.Println("After insertion:", insert(intervals, newInterval))

	intervals = [][]int{{1, 5}}
	newInterval = []int{2, 3}
	fmt.Println("Before insertion:", intervals)
	fmt.Println("New interval:", newInterval)
	fmt.Println("After insertion:", insert(intervals, newInterval))

	intervals = [][]int{{1, 5}}
	newInterval = []int{2, 7}
	fmt.Println("Before insertion:", intervals)
	fmt.Println("New interval:", newInterval)
	fmt.Println("After insertion:", insert(intervals, newInterval))
}
