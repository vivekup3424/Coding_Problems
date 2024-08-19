package main

func canFinish(numCourses int, prerequisites [][]int) bool {
	graph := make([][]int, numCourses)
	for i := 0; i < numCourses; i++ {
		graph[i] = make([]int, 0)
	}

	for _, pre := range prerequisites {
		a := pre[0]
		b := pre[1]
		graph[a] = append(graph[a], b)
	}

	visited := make([]int, numCourses)
	for i := 0; i < numCourses; i++ {
		if cycleDetection(graph, visited, i) {
			return false
		}
	}
	return true
}

func cycleDetection(adj [][]int, visited []int, node int) bool {
	if visited[node] == 1 {
		return true // cycle detected
	}
	if visited[node] == -1 {
		return false // already visited with no cycle
	}
	visited[node] = 1 // mark node as visited

	for _, neighbor := range graph[node] {
		if cycleDetection(graph, visited, neighbor) {
			return true
		}
	}
	visited[node] = -1 // mark node as visited and no cycle
	return false
}
