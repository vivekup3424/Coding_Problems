package main

import "fmt"

func searchMatrix(matrix [][]int, target int) bool {
	rows := len(matrix)
	cols := len(matrix[0])
	targetRow := -1
	//searching rowise
	for startRow, endRow := 0, rows-1; startRow <= endRow; {
		midRow := (startRow + endRow) / 2
		if matrix[midRow][0] <= target &&
			target <= matrix[midRow][cols-1] {
			targetRow = midRow
			break
		} else if matrix[midRow][0] > target {
			//move upwards(to smaller values)
			endRow = midRow - 1
		} else {
			//move downwards(to bigger values)
			startRow = midRow + 1
		}
	}
	if targetRow == -1 {
		return false
	} else {
		value := -1
		for start, end := 0, cols-1; start <= end; {
			mid := (start + end) / 2
			if matrix[targetRow][mid] == target {
				value = mid
				//fmt.Printf("Idx=%d\n", mid)
				break
			} else if matrix[targetRow][mid] > target {
				//move to lower value(leftwards)
				end = mid - 1
			} else {
				start = mid + 1
			}
		}
		///////////////
		if value == -1 {
			return false
		} else {
			return true
		}
	}
}

func main1() {
	matrix := [][]int{{1, 2, 3, 4},
		{7, 8, 9, 10},
		{11, 15, 16, 19}}
	target1 := 16
	target2 := 17
	target3 := 0
	target4 := 21
	target5 := 10
	fmt.Println(searchMatrix(matrix, target1))
	fmt.Println(searchMatrix(matrix, target2))
	fmt.Println(searchMatrix(matrix, target3))
	fmt.Println(searchMatrix(matrix, target4))
	fmt.Println(searchMatrix(matrix, target5))
}
