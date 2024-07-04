package main

import "fmt"

func main() {
	var n int
	fmt.Scan(&n)
	hashmap := make(map[string]int)
	for i := 0; i < n; i++ {
		var name string
		fmt.Scan(&name)
		if _, ok := hashmap[name]; ok {
			hashmap[name]++
			fmt.Printf("%v%v\n", name, hashmap[name])
		} else {
			hashmap[name] = 0
			fmt.Println("OK")
		}
	}
}
