package main

import "container/heap"
//defining the minHeap
type Heap []int
func (m Heap) Len() int{
	return len(m)	
}
func (h Heap) Less(i,j int) bool{
	return h[i] < h[j]
}
func (h Heap) Swap(i,j int) {
	h[i],h[j] = h[j],h[i]
}
func (h *Heap) Push(x int){
	*h = append(*h, x)
}
func (h *Heap) Pop(){
	old := *h
	n := len(old)
	x := old(n-1)
	*h := old[0:n-1]
	return x
}
func maxScoreWords(words []string, letters []byte, score []int) int {
	n := len(words)
	hashmap := make(map[rune]Heap)
	m := len(letters)
	for i := m{
		hashmap
	}
}

func main(){
	
}