package main

import "fmt"

func numTrees(n int) int {
	dp := make([]int, n+1)
	for i := 0; i <= n; i++ {
		if i == 0 {
			dp[i] = 1
		} else if i == 1 {
			dp[i] = 1
		} else {
			for j := 0; j <= i; j++ {
				dp[i] += (dp[j] * dp[i-j])
			}
		}
	}
	fmt.Println(dp)
	return dp[len(dp)-1]
}

//func main() {
//	n := 3
//	fmt.Println(numTrees(n))
//}
