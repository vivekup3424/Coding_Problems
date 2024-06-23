package main

func checkSubarraySum(nums []int, k int) bool {
	n := len(nums)
	if n < 2 {
		return false
	}
	hashmap := make(map[int][]int, 0)
	pref := make([]int, n)
	for i := 0; i < n; i++ {
		if i == 0 {
			pref[i] = nums[i]
		} else {
			pref[i] = nums[i] + pref[i-1]
			if pref[i]%k == 0 && i >= 1 {
				return true
			}
		}
		rem := pref[i] % k
		hashmap[rem] = append(hashmap[rem], i)
	}
	//traverse the hashmap
	for _, val := range hashmap {
		if len(val) > 1 && (val[len(val)-1]-val[0] != 0) {
			return true
		}
	}
	return false
}
