package main

import "fmt"

func main() {
	var n int
	fmt.Scan(&n)
	var a = make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&a[i])
	}
	var odds, evens, oddIdx, evenIdx int
	for i := 0; i < n; i++ {
		if a[i]%2 == 0 {
			evens++
			evenIdx = i
		} else {
			odds++
			oddIdx = i
		}
	}
	if odds == 1 {
		fmt.Println(oddIdx + 1)
	} else {
		fmt.Println(evenIdx + 1)
	}
}
