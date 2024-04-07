package main

func twoSum(nums []int, target int) []int {
	mp := make(map[int]int) //store element-index

	for idx, ele := range nums {
		diff := target - ele
		if idx2, exists := mp[diff]; exists {
			return []int{idx, idx2}
		} else {
			mp[ele] = idx
		}
	}
	return nil
}
