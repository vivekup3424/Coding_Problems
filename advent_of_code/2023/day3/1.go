package main

import (
	"fmt"
	"log"
	"os"
	"strings"
)

type Direction struct {
	x int
	y int
}

func isDigit(i byte) bool {
	return i >= '0' && i <= '9'
}
func isValid(x, y, rows, cols int) bool {
	return x >= 0 && x < rows && y >= 0 && y < cols
}
func main2() {
	directions := []Direction{
		{1, 0}, {0, 1}, {-1, 0}, {0, -1},
		{1, 1}, {-1, 1}, {1, -1}, {-1, -1},
	}

	//writer := bufio.NewWriter(os.Stdout)
	//reader := bufio.NewReader(os.Stdin)
	//writer.WriteString("Write the relative filepath to the input:-\n")
	//writer.Flush()
	//p, _ := reader.ReadString('\n')
	//p = strings.TrimSpace(p)
	data, err := os.ReadFile("./1_short.txt")
	if err != nil {
		log.Println(err)
	}
	dataString := string(data)
	rowValues := strings.Split(dataString, "\n")
	rows, cols := len(rowValues), len(rowValues[0])
	markedValues := make([][]bool, rows)
	for i := range markedValues {
		markedValues[i] = make([]bool, cols)
	}
	fmt.Printf("row = %v, cols = %v\n", rows, cols)
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			element := rowValues[i][j]
			if isDigit(element) {
				isPart := false
				for _, dir := range directions {
					x, y := i+dir.x, j+dir.y
					fmt.Printf("x = %v, y = %v\n", x, y)
					if isValid(x, y, rows, cols) && isValid(x, 0, rows, len(rowValues[x])) && !isDigit(rowValues[x][y]) && rowValues[x][y] != '.' {
						isPart = true
						break
					}
				}
				if isPart {
					//mark all the lefthand digits
					x := i
					for x >= 0 && isDigit(rowValues[x][j]) {
						markedValues[x][j] = true
						x--
					}
				}
			}

		}
	}
	//after marking all relevant values
	sum := 0
	for i := 0; i < rows; i++ {
		value := 0
		for j := 0; j < cols; j++ {
			if isDigit(rowValues[i][j]) {
				if markedValues[i][j] {
					value = (10 * value) + int(rowValues[i][j]-'0')
				} else {
					sum += value
					value = 0
				}
			}
		}
		sum += value
	}
	fmt.Println("Sum = ", sum)
}
