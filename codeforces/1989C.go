/*
*
If a person is asked to leave a review for the movie, then:

	if that person liked the movie, they will leave a positive review, and the movie's rating will increase by 1

;
if that person disliked the movie, they will leave a negative review, and the movie's rating will decrease by 1

	;
	otherwise, they will leave a neutral review, and the movie's rating will not change.

Every person will review exactly one movie — and for every person, you can choose which movie they will review.

The company's rating is the minimum of the ratings of the two movies. Your task is to calculate the maximum possible rating of the company.
*/
package main

import "fmt"

func main() {
	//input a variable t, as number of testcases
	var t int
	fmt.Scanf("%d", &t)
	for i := 0; i < t; i++ {
		var n int
		fmt.Scan(&n)
		//make two slices a, and b holding reviews of n people
		a := make([]int, n)
		b := make([]int, n)
		for j := 0; j < n; j++ {
			fmt.Scan(&a[j])
		}
		for j := 0; j < n; j++ {
			fmt.Scan(&b[j])
		}
		var actual_A, actual_B, neg, pos int
		//neg = number of points where both movies have negative reviews
		//pos = number of points where both movies have positive reviews
		for j := 0; j < n; j++ {
			if a[j] > b[j] {
				actual_A += a[j]
			} else if b[j] > a[j] {
				actual_B += b[j]
			} else if a[j] == 1 && b[j] == 1 {
				pos++
			} else if a[j] == -1 && b[j] == -1 {
				neg++
			}
		}

		//iterating over the reviews where a[i] == b[i]
		maxi := -10000000003
		for j := -neg; j <= pos; j++ {
			temp_a := actual_A + j
			temp_b := actual_B + pos - neg - j
			maxi = max(maxi, min(temp_a, temp_b))
		}
		fmt.Println(maxi)
	}
}
