package main

func checkXMatrix(grid [][]int) bool {
	n := len(grid)

	// Check diagonals
	for i := 0; i < n; i++ {
		if grid[i][i] == 0 || grid[i][n-1-i] == 0 {
			return false
		}
	}

	// Check non-diagonals
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			if i != j && j != n-1-i && grid[i][j] != 0 {
				return false
			}
		}
	}

	return true
}
