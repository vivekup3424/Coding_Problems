package main

import "slices"

type coordinate struct {
	x int
	y int
}

func isValidSudoku(board [][]byte) bool {
	row_map := map[int][]byte{}
	col_map := map[int][]byte{}
	box_map := map[coordinate][]byte{}
	for i := 0; i < 9; i++ {
		for j := 0; j < 9; j++ {
			val := board[i][j]
			if val != byte('.') {
				if (slices.Contains(row_map[i], val) ||
					slices.Contains(col_map[j], val) ||
					slices.Contains(coordinate{i, j}, val)) {
					return false
				}
				row_map[i] = append(row_map[i], val)
				col_map[j] = append(col_map[j], val)
				box_map(coordinate{i, j}) = append(box_map(coordinate{i, j}), val)

			}
		}
	}
	return true
}
