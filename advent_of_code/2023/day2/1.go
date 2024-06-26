package main

import (
	"fmt"
	"log"
	"strconv"
	"strings"
)

// Answer struct to hold the game details
type Answer struct {
	id    int
	green int
	blue  int
	red   int
}

// parseNumber extracts the numeral value before the given index
func parseNumber(str string, idx int) int {
	//get numeral value before idx
	var numBuffer []byte
	for i := idx - 1; i >= 0; i-- {
		if str[i] >= '0' && str[i] <= '9' {
			numBuffer = append(numBuffer, str[i])
		} else if str[i] == ' ' {
			break
		}
	}
	//reverse the numBuffer values
	for i, j := 0, len(numBuffer)-1; i < j; i, j = i+1, j-1 {
		numBuffer[i], numBuffer[j] = numBuffer[j], numBuffer[i]
	}
	numStr := string(numBuffer)
	num, err := strconv.Atoi(numStr)
	if err != nil {
		log.Println("Could not convert string to integer:", err)
		return 0
	}
	return num
}

// parseString parses the input string to extract the game information
func parseString(str string) *Answer {
	answer := new(Answer)
	// Get the index of ":"
	idxColon := strings.Index(str, ":")
	if idxColon == -1 {
		log.Println("Colon not found in the string")
		return answer
	}

	// Parse the game ID
	answer.id = parseNumber(str, idxColon)

	// Get the rounds part of the string
	roundsStr := str[idxColon+1:]
	rounds := strings.Split(roundsStr, ";")
	for _, round := range rounds {
		round = strings.TrimSpace(round)
		if idxRed := strings.Index(round, "red"); idxRed != -1 {
			answer.red = max(answer.red, parseNumber(round, idxRed))
		}
		if idxBlue := strings.Index(round, "blue"); idxBlue != -1 {
			answer.blue = max(answer.blue, parseNumber(round, idxBlue))
		}
		if idxGreen := strings.Index(round, "green"); idxGreen != -1 {
			answer.green = max(answer.green, parseNumber(round, idxGreen))
		}
	}
	return answer
}

func main() {
	//data, err := os.ReadFile("./1.txt")
	//if err != nil {
	//	log.Println(err)
	//}
	//dataString := string(data)
	//rowValues := strings.Split(dataString, "\n")
	maxBlues, maxReds, maxGreens := 14, 12, 13
	sum := 0

	//for _, row := range rowValues {
	//	ans := parseString(row)
	//	if ans.blue >= maxBlues && ans.green >= maxGreens && ans.red >= maxReds {
	//		sum += ans.id
	//	}
	//}
	input := "Game 88: 7 green, 3 red, 10 blue; 8 blue, 8 red, 3 green; 18 green, 1 blue, 7 red; 8 red, 7 green, 10 blue"
	ans := parseString(input)
	if ans.blue <= maxBlues && ans.green <= maxGreens && ans.red <= maxReds {
		sum += ans.id
	}

	fmt.Println("Sum = ", sum)
}
