"""
17. Letter Combinations of a Phone Number
https://leetcode.com/problems/letter-combinations-of-a-phone-number/

Given a string containing digits from 2-9 inclusive, return all possible
letter combinations that the number could represent. Return the answer in any
order.

A mapping of digits to letters (just like on the telephone buttons) is given
below. Note that 1 does not map to any letters.

    2 -> abc    3 -> def
    4 -> ghi    5 -> jkl    6 -> mno
    7 -> pqrs   8 -> tuv    9 -> wxyz

Example 1:
    Input:  digits = "23"
    Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Example 2:
    Input:  digits = ""
    Output: []

Example 3:
    Input:  digits = "2"
    Output: ["a","b","c"]

Constraints:
    - 0 <= digits.length <= 4
    - digits[i] is a digit in the range ['2', '9'].
"""
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
        def recurse(digits: str, index: int, temp: List[str]):
            if index == len(digits):
                answer.append("".join(temp))
                return
            for char in characters_map[digits[index]]:
                temp.append(char)
                recurse(digits, index + 1, temp)
                temp.pop()

        if digits:
            recurse(digits, 0, [])
        return answer