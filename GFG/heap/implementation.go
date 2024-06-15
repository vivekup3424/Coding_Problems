package main

import (
	"fmt"
)

// MaxHeap represents a max-heap.
type MaxHeap struct {
	Arr []int
}

// getLeftChild returns the index of the left child of the given node.
func getLeftChild(i int) int {
	return 2*i + 1
}

// getRightChild returns the index of the right child of the given node.
func getRightChild(i int) int {
	return 2*i + 2
}

// getParent returns the index of the parent of the given node.
func getParent(i int) int {
	return (i - 1) / 2
}

// swap swaps the elements at indices i and j.
func (m *MaxHeap) swap(i, j int) {
	m.Arr[i], m.Arr[j] = m.Arr[j], m.Arr[i]
}

// heapifyDown maintains the heap property by "bubbling down" the element at index i.
func (m *MaxHeap) heapifyDown(i int) {
	n := len(m.Arr)
	largest := i
	left := getLeftChild(i)
	right := getRightChild(i)

	if left < n && m.Arr[left] > m.Arr[largest] {
		largest = left
	}
	if right < n && m.Arr[right] > m.Arr[largest] {
		largest = right
	}
	if largest != i {
		m.swap(i, largest)
		m.heapifyDown(largest)
	}
}

// heapifyUp maintains the heap property by "bubbling up" the element at index i.
func (m *MaxHeap) heapifyUp(i int) {
	for i > 0 {
		parent := getParent(i)
		if m.Arr[i] > m.Arr[parent] {
			m.swap(i, parent)
			i = parent
		} else {
			break
		}
	}
}

// Push adds a new element to the heap.
func (m *MaxHeap) Push(x int) {
	m.Arr = append(m.Arr, x)
	m.heapifyUp(len(m.Arr) - 1)
}

// Pop removes and returns the maximum element from the heap.
func (m *MaxHeap) Pop() int {
	if len(m.Arr) == 0 {
		return -1 // Or an appropriate error value
	}
	top := m.Arr[0]
	last := len(m.Arr) - 1
	m.Arr[0] = m.Arr[last]
	m.Arr = m.Arr[:last]
	m.heapifyDown(0)
	return top
}

func main() {
	mh := &MaxHeap{}
	mh.Push(10)
	mh.Push(20)
	mh.Push(5)
	mh.Push(30)

	fmt.Println(mh)
	fmt.Println(mh.Pop()) // Should print 30
	fmt.Println(mh)
	fmt.Println(mh.Pop()) // Should print 20
	fmt.Println(mh)
	fmt.Println(mh.Pop()) // Should print 10
	fmt.Println(mh)
	fmt.Println(mh.Pop()) // Should print 5
}
