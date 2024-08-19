package main

import "go/format"

type coordinate struct{
	x int
	y int
}
func isValidSudoku(board [][]byte) bool {
	row_map := map[int][]int{}
	col_map := map[int][]int{}
	box_map := map[coordinate][]int{}
	for i := 0;i < 
	return false
}
