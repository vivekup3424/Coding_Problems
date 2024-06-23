package main

func insert(intervals [][]int, newInterval []int) [][]int {
	var ans [][]int
	n := len(intervals)
	for i := 0; i < n; i++ {
		if intervals[i][1] < newInterval[0] ||
			intervals[i][0] > newInterval[1] {
			//interval comes before the newInterval,
			//2.Interval comes wholly after the newInterval
			ans = append(ans, intervals[i])
		} else {
			//we have to merging
			start := intervals[i][0]
			end := newInterval[1]
			for intervals[i][0] <= end {
				end = max(intervals[i][1], end)
				i++
			}
			ans = append(ans, []int{start, end})
		}
	}
	return ans
}
