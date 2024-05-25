package main

import "sort"

type Interface interface {
	sort.Interface
	Push(x any) // add x as element Len()
	Pop() any   // remove and return element Len() - 1.
}

type intergerHeap []int

// gets the length of integer heap
func (iheap intergerHeap) Len() int { return len(iheap) }
func (iheap intergerHeap) Less(i, j int) bool {
	return iheap[i] < iheap[j]
}
func (iheap intergerHeap) Swap(i, j int) {
	iheap[i], iheap[j] = iheap[j], iheap[i]
}
