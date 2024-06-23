package main

func setZeroes(matrix [][]int) {
	firstRowZero := false
	m, n := len(matrix), len(matrix[0])
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			if i == 0 && matrix[0][j] == 0 {
				firstRowZero = true
			} else if matrix[i][j] == 0 {
				matrix[i][0] = -1
				matrix[0][j] = -1
			}
		}
	}

	for i := 1; i < m; i++ {
		for j := 1; j < n; j++ {
			if matrix[i][0] == -1 || matrix[0][j] == -1 {
				matrix[i][j] = 0
			}
		}
	}
	if matrix[0][0] == -1 {
		matrix[0][0] = 0
		for i := 0; i < m; i++ {
			matrix[i][0] = 0
		}
	}
	if firstRowZero {
		for j := 0; j < n; j++ {
			matrix[0][j] = 0
		}
	}
}
