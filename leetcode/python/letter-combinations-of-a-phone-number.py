from typing import List
class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        characters_map = {
            "2": ["a", "b", "c"],
            "3": ["d", "e", "f"],
            "4": ["g", "h", "i"],
            "5": ["j", "k", "l"],
            "6": ["m", "n", "o"],
            "7": ["p", "q", "r", "s"],
            "8": ["t", "u", "v"],
            "9": ["w", "x", "y", "z"],
        }
        answer : List[str] = []
        def recurse(digits: str, index: int, temp: str):
            for char in characters_map[digits[index]]:
                temp+=char


        return answer