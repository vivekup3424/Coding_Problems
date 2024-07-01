package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
)

var (
	onlyNumbers = regexp.MustCompile(`\d+`)
	onlySymbols = regexp.MustCompile(`[^.0-9]`)
)

func main() {
	if len(os.Args) != 2 {
		fmt.Fprintln(os.Stderr, "usage: go run main.go input.txt")
		os.Exit(1)
	}

	f, err := os.Open(os.Args[1])
	if err != nil {
		fmt.Fprintln(os.Stderr, "invalid file:", err)
		os.Exit(1)
	}
	defer f.Close()

	numberLocations := map[Coordinate]**int{}
	symbolLocations := []Coordinate{}
	var row, sum int
	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		data := scanner.Bytes()

		numberIndexes := onlyNumbers.FindAllIndex(data, -1)
		for _, location := range numberIndexes {
			index := location[0]
			size := location[1]
			ParseNumber(numberLocations, data, row, index, size)
		}

		symbolIndexes := onlySymbols.FindAllIndex(data, -1)
		for _, location := range symbolIndexes {
			symbolLocations = append(symbolLocations, Coordinate{Row: row, Col: location[0]})
		}
		row++
	}

	direction := []bool{false, true, false, false, true, true, false, false}
	inc := []int{1, 1, -1, -1, -1, -1, 1, 1}
	for _, coord := range symbolLocations {
		for i, incRow := range direction {
			if incRow {
				coord.Row += inc[i]
			} else {
				coord.Col += inc[i]
			}
			if v, ok := numberLocations[coord]; ok && *v != nil {
				sum += **v
				*v = nil
			}
		}
	}

	fmt.Fprintln(os.Stdout, "The sum of all of the part numbers in the engine schematic is:", sum)
}

func ParseNumber(locations map[Coordinate]**int, data []byte, row, startIdx, size int) {
	value := new(int)
	for i, m := size-1, 1; i >= startIdx; i, m = i-1, m*10 {
		*value += int(data[i]-'0') * m
		locations[Coordinate{Row: row, Col: i}] = &value
	}
}

type Coordinate struct {
	Col int
	Row int
}

