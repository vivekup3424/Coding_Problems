package main

import "fmt"

/*
Polycarpus has a ribbon, its length is n. He wants to cut the ribbon in a way that fulfils the following two conditions:

	After the cutting each ribbon piece should have length a, b or c.
	After the cutting the number of ribbon pieces should be maximum.

Help Polycarpus and find the number of ribbon pieces after the required cutting.
Input

The first line contains four space-separated integers n, a, b and c (1 ≤ n, a, b, c ≤ 4000) — the length of the original ribbon and the acceptable lengths of the ribbon pieces after the cutting, correspondingly. The numbers a, b and c can coincide.
*/
func main() {
	var n, a, b, c int
	fmt.Scanf("%d %d %d %d\n", &n, &a, &b, &c)
	numRibbons := make([]int, n+1)
}
