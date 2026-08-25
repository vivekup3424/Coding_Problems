"""
345. Reverse Vowels of a String
https://leetcode.com/problems/reverse-vowels-of-a-string/

Given a string s, reverse only all the vowels in the string and return it.

The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both cases.

Example 1:
    Input:  s = "IceCreAm"
    Output: "AceCreIm"
    Explanation: The vowels in s are ['I', 'e', 'e', 'A']. On reversing the
    vowels, s becomes "AceCreIm".

Example 2:
    Input:  s = "leetcode"
    Output: "leotcede"

Constraints:
    - 1 <= s.length <= 3 * 10^5
    - s consists of printable ASCII characters.
"""
class Solution:
    @staticmethod
    def isVowel(c):
        vowels = ['a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U']
        if(c in vowels):
            return True
        return False
    def reverseVowels(self, s: str) -> str:
        arr = []
        for c in s:
            
