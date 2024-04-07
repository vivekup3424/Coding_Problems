package main

func trailingZeroes(n int) int {
	countFive := 0
	temp := n
	//counter := 0
	for temp > 0 {
		//counter++
		countFive += (temp / 5)
		temp /= 5
	}
	return countFive
}
