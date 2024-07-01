package tokenizer

func Tokenizer(s string) []string {
	stop_words := []byte{
		' ',
		':',
		';',
		',',
		'\n',
	}
	stop_words_map := make(map[byte]bool)
	for _, stop_word := range stop_words {
		stop_words_map[stop_word] = true
	}
	ans := []string{}
	start, end := 0, 0
	n := len(s)
	for end < n {
		char := s[end]
		if stop_words_map[char] {
			if start < end {
				ans = append(ans, s[start:end])

			}
			start = end + 1
		}
		end++
	}
	if start < end {
		ans = append(ans, s[start:end])
	}
	return ans
}
