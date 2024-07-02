package main

import (
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

// Extracts the ID of the card from the input string
func getId(input string) int {
	idxD := strings.Index(input, "d")
	idxColon := strings.Index(input, ":")
	s := input[idxD+2 : idxColon]
	s = strings.TrimSpace(s)
	num, err := strconv.Atoi(s)
	if err != nil {
		log.Fatalf("Failed to convert string to integer: %v", err)
	}
	return num
}

// Counts the number of matches between the winning numbers and the actual numbers
func getCount(input string) int {
	idxColon := strings.Index(input, ":")
	idxDash := strings.Index(input, "|")
	winningPart := input[idxColon+1 : idxDash]
	actualPart := input[idxDash+1:]

	winningNumbers := make(map[string]bool)
	for _, num := range strings.Fields(winningPart) {
		winningNumbers[num] = true
	}

	count := 0
	for _, num := range strings.Fields(actualPart) {
		if winningNumbers[num] {
			count++
		}
	}
	return count
}

func main() {
	//reader := bufio.NewReader(os.Stdin)
	//fmt.Print("Write relative path to the input file: ")
	//path, err := reader.ReadString('\n')
	//if err != nil {
	//	log.Fatalf("Failed to read input: %v", err)
	//}
	//path = strings.TrimSpace(path)

	data, err := os.ReadFile("./1.txt")
	if err != nil {
		log.Fatalf("Failed to read file: %v", err)
	}
	dataString := string(data)
	inputs := strings.Split(dataString, "\n")

	freqHashMap := make(map[int]int)
	for _, input := range inputs {
		if len(input) > 1 {
			id := getId(input)
			freqHashMap[id]++
		}
	}

	sum := 0
	for _, input := range inputs {
		if len(input) > 1 {
			id := getId(input)
			count := getCount(input)
			sum += freqHashMap[id]
			for i := 1; i <= count; i++ {
				freqHashMap[id+i] += freqHashMap[id]
			}
		}
	}
	fmt.Printf("Sum = %v\n", sum)
}
