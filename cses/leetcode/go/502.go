package main

import (
	"container/heap"
	"fmt"
	"sort"
)

type Project struct {
	Profit  int
	Capital int
}
type ByCapital []Project

func (a ByCapital) Len() int           { return len(a) }
func (a ByCapital) Swap(i, j int)      { a[i], a[j] = a[j], a[i] }
func (a ByCapital) Less(i, j int) bool { return a[i].Capital < a[j].Capital }

type MaxHeap []int

func (m MaxHeap) Len() int           { return len(m) }
func (m MaxHeap) Swap(i, j int)      { m[i], m[j] = m[j], m[i] }
func (m MaxHeap) Less(i, j int) bool { return m[i] > m[j] }
func (m *MaxHeap) Push(x interface{}) {
	*m = append(*m, x.(int))
}
func (m *MaxHeap) Pop() interface{} {
	old := *m
	n := len(old)
	x := old[n-1]
	*m = old[0 : n-1]
	return x
}
func findMaximizedCapital(k int, w int, profits []int, capital []int) int {
	n := len(profits)
	projects := []Project{}
	for i := 0; i < n; i++ {
		projects = append(projects, Project{Profit: profits[i], Capital: capital[i]})
	}
	fmt.Println(projects)
	sort.Sort(ByCapital(projects))
	fmt.Println("Sorted projects", projects)
	maxHeap := &MaxHeap{} //this a pointer
	heap.Init(maxHeap)
	index := 0
	for i := 0; i < k; i++ {
		for index < n && projects[index].Capital <= w {
			heap.Push(maxHeap, projects[index].Profit)
			index++
		}
		if maxHeap.Len() == 0 {
			break
		}
		w += heap.Pop(maxHeap).(int)
	}
	//1. Create a max-heap and store all the projects and have a capital requirement atmost the current capital which I have
	//2.max-heap to be sorted on the basis of their profit

	return w
}
