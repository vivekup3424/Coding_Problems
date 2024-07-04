package main

import "fmt"

func main() {
	maxi := 1000001
	numbers := make([]bool, maxi)
	primes := []int{} // using to store primes

	// Finding primes using sieve of Eratosthenes
	for i := 2; i*i < maxi; i++ {
		if !numbers[i] {
			primes = append(primes, i)
			for j := i * i; j < maxi; j += i {
				numbers[j] = true
			}
		}
	}
	//it can be shown the only squares of primes are the numbers who are t-primes, that is they have only 3 distinct positive divisors
	squares := map[int]bool{}
	for i := 0; i < len(primes); i++ {
		squares[primes[i]*primes[i]] = true
	}
	var n int
	fmt.Scan(&n)
	num := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&num[i])
		if squares[num[i]] {
			fmt.Println("YES")
		} else {
			fmt.Println("NO")
		}
	}
}
