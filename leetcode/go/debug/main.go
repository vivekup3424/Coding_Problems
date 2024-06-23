package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func maxProfit(prices []int) int {
	var diff []int
	for i := 0; i < len(prices)-1; i++ {
		diff = append(diff, prices[i+1]-prices[i])
	}
	n := len(diff)
	exclude := make([]bool, n)
	for key, val := range diff {
		fmt.Printf("Key = %v, Value = %v", key, val)
	}
	//exclude the negative and its neighboring minimum value
	for key, val := range diff {
		if val < 0 {
			exclude[key] = true
		}
		if key-1 >= 0 && exclude[key-1] {
			continue
		} else if key+1 < n && exclude[key+1] {
			continue
		} else {
			//if both of them are unmarked, mark the smallest smallest one
			if key == 0 && key+1 < n {
				exclude[key+1] = true
			} else if key == n-1 && key-1 >= 0 {
				exclude[key-1] = true
			} else {
				if diff[key-1] < diff[key+1] {
					exclude[key-1] = true
				} else {
					exclude[key+1] = true
				}
			}
		}
	}
	//get the sum of all positives
	sum := 0
	for key, val := range diff {
		if !exclude[key] {
			sum += val
		}
	}
	return sum
}
func main() {
	writer := bufio.NewWriter(os.Stdout)
	reader := bufio.NewReader(os.Stdin)
	writer.Write([]byte("Enter the length of the array: \n"))
	writer.Flush()
	input, _ := reader.ReadString('\n')
	n, _ := strconv.Atoi(input)
	arr := make([]int, n)
	writer.Write([]byte("Enter the elements of the array separated by spaces: \n"))
	writer.Flush()
	inputValues, _ := reader.ReadString('\n')
	values := strings.Split(strings.TrimSpace(inputValues), " ")
	if len(values) != n {
		fmt.Println("The number of elements does not match the specified length.")
		return
	}
	for i := 0; i < n; i++ {
		v, err := strconv.Atoi(values[i])
		if err != nil {
			fmt.Println("Invalid input. Please enter integers only.")
			return
		}
		arr[i] = v
	}
	fmt.Println("Maximum profit:", maxProfit(arr))
}
