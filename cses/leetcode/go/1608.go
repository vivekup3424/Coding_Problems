package main

import "sort"

type intSort []int

func (i intSort) Len() int           { return len(i) }
func (i intSort) Less(x, y int) bool { return i[x] < i[y] }
func (i intSort) Swap(x, y int)      { i[x], i[y] = i[y], i[x] }

func specialArray(nums []int) int {
	sortedNums := sort.Sort(intSort())
}
