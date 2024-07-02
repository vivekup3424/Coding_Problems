package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	writer := bufio.NewWriter(os.Stdout)
	reader := bufio.NewReader(os.Stdin)
	writer.WriteString("Write relative path to the input file:- ")
	writer.Flush()
	path, _ := reader.ReadString('\n')
	path = strings.TrimSpace(path)
	data, _ := os.ReadFile(path)
	dataString := string(data)
	inputs := strings.Split(dataString, "\n")

	sum := 0
	for _, input := range inputs {
		if len(input) > 1 {
			idxColor := strings.Index(input, ":")
			idxDash := strings.Index(input, "|")
			winningPart := input[idxColor+1 : idxDash]
			actualPart := input[idxDash+1:]
			//printing the winning numbers
			numbers := strings.Split(winningPart, " ")
			winningNumbers := make(map[string]bool)
			for _, num := range numbers {
				if num != "" {
					winningNumbers[num] = true
				}
			}

			actualNumbers := strings.Split(actualPart, " ")
			count := 0
			for _, num := range actualNumbers {
				if num != "" && winningNumbers[num] {
					count++
				}
			}
			if count > 0 {
				sum += (1 << (count - 1))
			}

		}
	}
	fmt.Printf("Sum = %v\n", sum)
}
