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
			if slices.Contains(row_map[i],val)
		}
	}
	return true
}
