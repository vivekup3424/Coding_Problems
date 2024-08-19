package main

import "fmt"

func dfs(graph [][]int, source int, visited map[int]bool) {
	if visited[source] == true {
		return
	}
	visited[source] = true
	for _, neighbor := range graph[source] {
		dfs(graph, neighbor, visivisited)
	}
}

func canFinish(numCourses int, prerequisites [][]int) bool {
	adj := make([][]int, numCourses)
	for _, edges := range prerequisites {
		adj[edges[0]] = append(adj[edges[0]], edges[1])
	}
	fmt.Println(adj)
	visited := make(map[int]bool)
	dfs(adj, 0, visited)
	return len(visited) == numCourses
}

func main() {
	numCourses := 5
	prerequisites := [][]int{{1, 0}, {2, 1}, {3, 2}, {4, 3}}
	result := canFinish(numCourses, prerequisites)
	fmt.Println("Can finish all courses:", result)
}
