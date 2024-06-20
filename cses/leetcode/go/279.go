/*
It is similar to coin change problem. just put all the perfect squares less than or equal to n in a vector and now its the same problem as the coin change, You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money., You may assume that you have an infinite number of each kind of coin.
*/
package main

import (
	"fmt"
	"math"
)

func numSquares(n int) int {
	var squares []int
	for i := 1; i <= int(math.Sqrt(float64(n))); i++ {
		squares = append(squares, int(i*i))
	}
	fmt.Println("Squares =", squares)
	dp := make()
}
