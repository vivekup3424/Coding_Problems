package main

import "fmt"

func canFinishTopo(prerequisities [][]int, numCourses int) bool {
	graph := make([][]int, numCourses)
	for i := 0; i < numCourses; i++ {
		graph[i] = make([]int, 0)
	}
	for _, pre := range prerequisities {
		a := pre[0]
		b := pre[1]
		graph[a] = append(graph[a], b)
	}
	fmt.Println("Graph = ", graph)
	indegree := make([]int, numCourses)
	for i := 0; i < numCourses; i++ {
		for _, node := range graph[i] {
			indegree[node]++
		}
	}
	fmt.Println("Indegrees = ", indegree)
	// doing topological sort

	return false
}
