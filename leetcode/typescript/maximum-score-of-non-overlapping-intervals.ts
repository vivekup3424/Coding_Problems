function maximumWeight(intervals: number[][]): number[] {
	let answer = [0]
	intervals.sort((a, b) => {
		return a[2] - b[2]
	})
	function recurse(intervals: number[][], i: number, n: number, : w) {
		return max(recurse(intervals, i - 1, n) + intervals[i][2], recurse((intervals, i - 1, n)))
	}
	console.log(intervals)
	//do a dp now to get the  maxValue
	return answer
};
