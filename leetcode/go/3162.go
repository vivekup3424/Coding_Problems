package main

func numberOfPairs(nums1 []int, nums2 []int, k int) int {
	for idx, val := range nums2 {
		nums2[idx] = val * k
	}
	var count int
	for i := 0; i < len(nums2); i++ {
		for j := 0; j < len(nums1); j++ {
			if nums2[i] != 0 && nums1[j]%nums2[i] == 0 {
				count++
			}
		}
	}
	return count
}
