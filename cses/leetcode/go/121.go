package main

func maxProfit(prices []int) int {
	maxSum, currentSum := 0, 0
	for i := 0; i < len(prices)-1; i++ {
		currentSum += prices[i+1] - prices[i]
		if currentSum < 0 {
			currentSum = 0
		}
		maxSum = max(maxSum, currentSum)
	}
	return maxSum
}

//func main() {
//	writer := bufio.NewWriter(os.Stdout)
//	writer.Write([]byte("Enter the length of the array: "))
//	writer.Flush()
//	reader := bufio.NewReader(os.Stdin)
//	input, _ := reader.ReadString('\n')
//	input = strings.TrimSpace(input)
//	n, _ := strconv.Atoi(input)
//	numbers := make([]int, n)
//	inputValues, _ := reader.ReadString('\n')
//	values := strings.Split(inputValues, " ")
//	for i := 0; i < n; i++ {
//		v, _ := strconv.Atoi(values[i])
//		numbers[i] = v
//	}
//	fmt.Println(maxProfit(numbers))
//}
