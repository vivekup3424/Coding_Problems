package main

import "fmt"

func subarraysDivByK(nums []int, k int) int {
	n := len(nums)
	pref := make([]int, n)
	mp := make(map[int]int)
	for i := 0; i < n; i++ {
		if i == 0 {
			pref[i] = nums[i]
		} else {
			pref[i] = pref[i-1] + nums[i]
		}
		rem := pref[i] % k
		mp[rem] += 1
	}
	//print the prefix sum
	fmt.Println(pref)
	fmt.Println(mp)
	sum := 0
	for key, val := range mp {
		if key == 0 {
			sum += val
			sum += (val * (val - 1)) / 2
		} else {
			sum += (val * (val - 1)) / 2
		}
	}
	fmt.Println("Sum = ", sum)
	return sum
}
