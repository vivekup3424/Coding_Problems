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

func twoSumsAgain(nums []int, target) []int {
	mp := make(map[int]int) //stores element-index
	for idx,val := range nums{
		elem2 := target - val
		if idx2, exists := mp[elem2]; exists{
			return []int{idx,idx2}
		}
	}
	return nil
}

func twoSumsFor(nums []int, target) []int{
	for i := 0; i < len(nums); i++{
		elem2 = target - nums[i]
		for j := i + 1; j <
	}
}
