package main

import (
	"fmt"
	"log"
	"os"
	"strings"
)

func main1() {

	file, err := os.ReadFile("./1.txt")
	if err != nil {
		log.Fatal(err)
	}
	fileString := string(file)
	//fmt.Println(fileString)
	instructions := strings.Split(fileString, "\n")
	//fmt.Println(instructions)
	var sum int
	//from each instruction get the value
	//using two-pointer approach
	for _, instruction := range instructions {
		l, r := 0, len(instruction)-1
		value := 0
		for l <= r {
			c := instruction[l]
			if '0' <= c && c <= '9' {
				element := int(instruction[l] - '0')
				value = value + 10*element
				break
			} else {
				l++
			}
		}
		for l <= r {
			c := instruction[r]
			if '0' <= c && c <= '9' {
				element := int(instruction[r] - '0')
				value = value + element
				break
			} else {
				r--
			}
		}
		fmt.Printf("For instruction = %s, value = %v\n", instruction, value)
		sum += value
	}
	fmt.Printf("Sum = %v\n", sum)
}
