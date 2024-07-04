package main

import (
	"fmt"
)

const INF int = 1000000000

func solve(n int, s string) int {
	minResult := INF
	for i := 0; i < n-1; i++ {
		sum := 0
		for j := 0; j < n; j++ {
			if j == i {
				num := int(s[j]-'0')*10 + int(s[j+1]-'0')
				if num == 0 {
					return 0
				} else if num != 1 {
					sum += num
				}
			} else if j == i+1 {
				continue
			} else {
				num := int(s[j] - '0')
				if num == 0 {
					return 0
				} else if num != 1 {
					sum += num
				}
			}
		}
		minResult = min(minResult, sum)
	}
	return minResult
}
func main1986D() {
	var t int
	fmt.Scan(&t)
	for i := 0; i < t; i++ {
		var n int
		fmt.Scan(&n)
		var s string
		fmt.Scan(&s)
		fmt.Println(solve(n, s))
	}
}
