package main

import "fmt"

type Race struct {
	Time     int
	Distance int
}

func findRange(r Race) int {
	speed := 0
	count := 0
	for i := 0; i < r.Time; i++ {
		leftOutTime := r.Time - i
		if speed*leftOutTime > r.Distance {
			fmt.Printf("Time = %v\n", i)
			count++
		}
		speed++
	}
	fmt.Printf("Count = %v\n", count)
	return count
}
func main() {
	races := []Race{
		{59796575, 597123410321328},
	}
	product := 1
	for _, r := range races {
		product *= findRange(r)
	}
	fmt.Println(product)
}
