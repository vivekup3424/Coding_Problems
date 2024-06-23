package main

// int minimumCost(int n, int w, vector<int> &cost) {
func minimumCost(n, w int, cost []int) {
	var dp [][]int //dimension (n+1)*(w+1)
	for i := 0; i < n+1; i++ {
		for j := 0; j < w+1; j++ {
			if i == 0 || j == 0 {
				dp[i][j] = 0
			} else if i+1 <= j {

			}
		}
	}

}
