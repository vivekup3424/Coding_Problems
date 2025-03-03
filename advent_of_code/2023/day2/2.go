package main

import (
	"bufio"
	"day2/tokenizer"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func main() {
	writer := bufio.NewWriter(os.Stdout)
	writer.WriteString("Write the relative file-path to the input file:-\n")
	writer.Flush()
	p, _ := bufio.NewReader(os.Stdin).ReadString('\n')
	p = strings.TrimSpace(p)
	fmt.Println(p)
	data, err := os.ReadFile(p)
	if err != nil {
		log.Println(err)
	}
	dataString := string(data)
	rowValues := strings.Split(dataString, "\n")
	sumProduct := 0

	//input := "Game 88: 7 green, 3 red, 10 blue; 8 blue, 8 red, 3 green; 18 green, 1 blue, 7 red; 8 red, 7 green, 10 blue"
	for _, input := range rowValues {
		tokens := tokenizer.Tokenizer(input)
		ans := &Answer{}
		for i := 0; i < len(tokens); i++ {
			switch tokens[i] {
			case "Game":
				ans.id, _ = strconv.Atoi(tokens[i+1])
			case "red":
				val, err := strconv.Atoi(tokens[i-1])
				if err != nil {
					log.Fatalln("Error converting to integer: red: ", err)
				}
				ans.red = max(ans.red, val)
			case "blue":
				val, err := strconv.Atoi(tokens[i-1])
				if err != nil {
					log.Fatalln("Error converting to integer: blue: ", err)
				}
				ans.blue = max(ans.blue, val)
			case "green":
				val, err := strconv.Atoi(tokens[i-1])
				if err != nil {
					log.Fatalln("Error converting to integer: green: ", err)
				}
				ans.green = max(ans.green, val)
			}
		}

		sumProduct += ans.red * ans.blue * ans.green
	}
	fmt.Println("Sum of Products = ", sumProduct)
}
