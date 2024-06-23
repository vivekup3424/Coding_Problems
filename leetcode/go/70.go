package main

func climbStairs(n int) int {
	oneStep, twoStep := 1, 2
	current := 0
	for i := 1; i <= n; i++ {
		if i == 1 {
			current = oneStep
		} else if i == 2 {
			current = twoStep
		} else {
			current = oneStep + twoStep
			oneStep = twoStep
			twoStep = current
		}
	}
	return current
}

//func main() {
//	writer := bufio.NewWriter(os.Stdout)
//	writer.Write([]byte("Enter the number of steps: "))
//	writer.Flush()
//	reader := bufio.NewReader(os.Stdin)
//	input, _ := reader.ReadString('\n')
//	input = strings.TrimSpace(input)
//	n, _ := strconv.Atoi(input)
//	fmt.Println(climbStairs(int(n)))
//}
