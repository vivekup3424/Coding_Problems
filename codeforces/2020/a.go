package main

import "fmt"

func a() {
	n, k := 0, 0
	_, err := fmt.Scan(&n, &k)
	//finding the log n base k
	temp := 0
	rem := 0
	for n > 0 {
		rem = n % k
		n = n / k
		temp += 1
	}
	fmt.Println("%v", temp+rem)
}
