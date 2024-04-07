package main

func isAnagram(s string, t string) bool {
	st1 := make(map[rune]int) //frequency hash-set for each character
	st2 := make(map[rune]int)

	for _, elem := range s {
		if _, hashNum := st1[elem]; hashNum {
			st1[elem]++
		} else {
			st1[elem] = 1
		}
	}

	for _, elem := range t {
		if _, hashNum := st2[elem]; hashNum {
			st2[elem]++
		} else {
			st2[elem] = 1
		}
	}

	//check if character frequencies are equal
	if len(st1) > len(st2) {
		for char, countS := range st1 {
			countT, ok := st2[char]
			if !ok || countT != countS {
				return false
			}
		}
	}
	for char, countS := range st2 {
		countT, ok := st1[char]
		if !ok || countT != countS {
			return false
		}
	}
	return true
}
