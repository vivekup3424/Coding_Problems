class Solution:
    def containsSubstring(self, string: str, substring: str) -> bool:
        return substring in string

    def maxRepeating(self, sequence: str, word: str) -> int:
        if not word or len(word) > len(sequence):
            return 0
        
        l, r = 0, len(sequence) // len(word)
        answer = 0

        while l <= r:
            m = (l + r) // 2
            newString = word * m
            if self.containsSubstring(sequence, newString):
                answer = m
                l = m + 1
            else:
                r = m - 1

        return answer

# Example usage
sol = Solution()
sequence = "abababab"
word = "ab"
print(sol.maxRepeating(sequence, word))  # Output: 4
