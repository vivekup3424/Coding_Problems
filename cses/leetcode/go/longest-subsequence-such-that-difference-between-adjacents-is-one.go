package main

func longestSubsequenceWithDiffOne(a []int, n int) {
	visited := make([]bool, n) //zero value - false
	maxLength := 0
	for i := 0; i < n; i++ {
		if visited[i] == false {
			currenLength := 1
			prev := a[i]
			visited[i] = true
			for j := i + 1; j < n; j++ {
				if (prev - a[j]) == 1 {
					currenLength++
					visited[j] = true
					prev = a[j]
				}
			}
			maxLength = max(maxLength, currenLength)

		}
	}
	return maxLength
}
