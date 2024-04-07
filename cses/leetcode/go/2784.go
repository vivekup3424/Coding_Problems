package main

func gcd(a, b int) int {
	if a == 0 {
		return b
	} else {
		return gcd(b%a, a)
	}
}

func isGoodArray(nums []int) bool {
	a := nums[0]
	for _, ele := range nums {
		a = gcd(a, ele)
	}
	return a == 1
}
