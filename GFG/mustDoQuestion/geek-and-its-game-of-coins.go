package main

func findWinner(n, x, y int) int {
	round := 0
	for n > 0 {
		//Bob's tunr
		if round%2 == 0 {
			if n >= x {
				n -= x
			} else {
				n -= 1
			}
		} else {
			//Alice turn
			if n >= y {
				n -= y
			} else {
				n -= 1
			}
		}
		round++
	}
	return round % 2
}
