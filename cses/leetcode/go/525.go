package main

func findMaxLength(nums []int) int {
	n := len(nums)
	sum := 0
	sumToIndices := make(map[int][]int)
	maxLength := 0
	for i := 0; i < n; i++ {
		if nums[i] == 1 {
			sum++z
		} else {
			sum--
		}
		sumToIndices[sum] = append(sumToIndices[sum], i) // Correct syntax for appending to slice in map
		if _, ok := sumToIndices[sum]; ok {
			if sum == 0 {
				maxLength = i + 1
			} else if maxLength < i-sumToIndices[sum][0] {
				maxLength = i - sumToIndices[sum][0]
			}
		}
	}
	return maxLength
}
