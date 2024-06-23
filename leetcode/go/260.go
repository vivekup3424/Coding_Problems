package main

func singleNumber(nums []int) []int {
	mp := make(map[int]int)
	for _, val := range nums {
		mp[val] += 1
	}
	var v []int
	for key, val := range mp {
		if val == 1 {
			v = append(v, key)
		}
	}
	return v
}
