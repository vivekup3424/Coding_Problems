package main

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
		for start, end := matrix[targetRow][0], matrix[targetRow][cols-1]; start <= end; {
			mid := (start + end) / 2
			if mid == target {
				value = mid
				break
			} else if mid > target {
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
