package main

func isAnagram(s string, t string) bool {
	if len(s) != len(t) {
		return false
	}
	count_s := map[rune]int{}
	count_t := map[rune]int{}
	for _, c := range s {
		count_s[c] += 1
	}
	for _, c := range t {
		count_t[c] += 1
	}

	for key, val := range count_s {
		if count_t[key] != val {
			return false
		}
	}
	return true
}
