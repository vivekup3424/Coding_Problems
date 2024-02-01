from collections import defaultdict
class Solution:
    def makeEqual(self, words: List[str]) -> bool:
        hashMap = defaultdict({})
        for word in words:
            sum += len(word)

        if sum % len(words) == 0 :
            return True
        else:
            return False