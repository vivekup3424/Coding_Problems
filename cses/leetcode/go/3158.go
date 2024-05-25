package main

// =============================================================//
// ----------------BITWISE OPERATIONS---------------------------//
// =============================================================//
func duplicateNumbersXOR(nums []int) int {
	freq := make(map[int]int)
	for _, value := range nums {
		freq[value] += 1
	}
	var sum int = 0
	for key, frequency := range freq {
		if frequency > 1 {
			sum ^= key
		}
	}
	return sum
}
