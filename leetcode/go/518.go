package main

func change(amount int, coins []int) int {
	dp := make([]int, amount+1) //num of ways
	dp[0] = 1
	for _, coin := range coins {
		for i := coin; i <= amount; i++ {
			dp[i] += dp[i-coin]
		}
	}
	return dp[amount]
}
