package main

import (
	"fmt"
)

func compressedString(word string) string {
	var ans string
	for i := 0; i < len(word); i++ {
		c := word[i]
		l := 0
		for ; i < len(word) && c == word[i]; i++ {
			l++
		}
		div := l / 9
		fmt.Println(div)
		for ; div >= 0; div-- {
			ans = ans + fmt.Sprintf("9%c", c)
		}
		if l%9 != 0 {
			ans = ans + fmt.Sprintf("%d%c", l%9, c)
		}
	}
	fmt.Println(ans)
	return ans
}
