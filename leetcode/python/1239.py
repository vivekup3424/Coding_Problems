class Solution:
    def maxLength(self, arr) -> int:
        words = [""]
        maxLength = 0
        for s in arr:
            for word in words:
                newWord = word + s
                if len(newWord) != len(set(newWord)):
                    # pruning
                    continue
                else:
                    maxLength = max((maxLength, len(newWord)))
                    words.append(newWord)
        return maxLength


arr = ["un", "iq", "ue"]
a = Solution().maxLength(arr)
print(a)
