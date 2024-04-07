package main

func isSubstringPresent(s string) bool {
	hashset := make(map[string]bool)

	for l := 1; l < len(s); l++ {
		a := s[l-1 : l+1]
		hashset[a] = true
		b := string(s[l]) + string(s[l-1])
		if hashset[b] {
			return true
		}
	}
	return false
}
