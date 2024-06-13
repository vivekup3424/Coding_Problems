package main

import "math"

func colorGraph(graph [][]int, vtx, clr int, colors []int) {
	newColor := int(math.Abs((float64)(1 - clr)))
}
func isBipartite(graph [][]int) bool {
	V := len(graph)
	colors := make([]int, V)
	for i := range colors {
		colors[i] = -1
	}

	for i := 0; i < V; i++ {
		if colors[i] == -1 {

		}
	}
}

func main() {

}
