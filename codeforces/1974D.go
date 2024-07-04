package main

import "fmt"

func solve(n int, s string) string {
	if n%2 == 1 {
		return "NO"
	}
	freqHash := make(map[byte]int)
	freqHash['N'] = 0
	freqHash['E'] = 0
	freqHash['W'] = 0
	freqHash['S'] = 0

	for i := 0; i < n; i++ {
		freqHash[s[i]]++
	}
	fmt.Println(freqHash)
	minN := min(freqHash['N'], freqHash['S'])
	minE := min(freqHash['E'], freqHash['W'])
	freqHash['N'] -= minN
	freqHash['S'] -= minN
	freqHash['E'] -= minE
	freqHash['W'] -= minE
	if freqHash['N']%2 != 0 || freqHash['E']%2 != 0 || freqHash['S']%2 != 0 || freqHash['W']%2 != 0 {
		return "NO"
	}
	return "YES"
}
func main() {
	var t int
	fmt.Scan(&t)
	for i := 0; i < t; i++ {
		var n int
		fmt.Scan(&n)
		var s string
		fmt.Scan(&s)
		fmt.Println(solve(n, s))
	}
}
