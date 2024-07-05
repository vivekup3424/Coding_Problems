package main

import "fmt"

func main() {
	var n, a, b, c int
	fmt.Scanf("%d %d %d %d\n", &n, &a, &b, &c)
	dp := make([]int, n+1)
	//for i := n; i >= 0; i-- {
	//	if i+a <= n {
	//		dp[i] = max(dp[i], dp[i+a]+1)
	//	}
	//	if i+b <= n {
	//		dp[i] = max(dp[i], dp[i+b]+1)
	//	}
	//	if i+c <= n {
	//		dp[i] = max(dp[i], dp[i+c]+1)
	//	}
	//}
	for i := 0; i <= n; i++ {
		if i-a >= 0 {
			dp[i] = max(dp[i], dp[i-a]+1)
		}
		if i-b >= 0 {
			dp[i] = max(dp[i], dp[i-b]+1)
		}
		if i-c >= 0 {
			dp[i] = max(dp[i], dp[i-c]+1)
		}
	}
	fmt.Println(dp[0])
}
