package main

type SortBy []int

func (a SortBy) Len() int           { return len(a) }
func (a SortBy) Swap(i, j int)      { a[i], a[j] = a[j], a[i] }
func (a SortBy) Less(i, j int) bool { return a[i] < a[j] }
func numberOfArithmeticSlices(nums []int) int {
	nums = SortBy(nums)
	maxDiff := nums[len(nums)-1] - nums[0]
	dp := make(map[int]int)
	// dp[i][j] = #sequences ending at index i, with diff of j
	n := len(nums)
	for i := 0; i < n; i++ {
		for j := 0; j < i; j++ {
			diff := nums[i] - nums[j]
			dp[i][diff] += dp[j][diff] + 1
		}
	}

}
func main() {

}
