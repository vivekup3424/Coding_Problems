"""
Roll Characters of String
https://www.geeksforgeeks.org/problems/roll-the-characters-of-a-string2127/1

Given a string s and an integer array roll, where roll[i] means rolling the
first roll[i] characters of the string, apply every roll[i] on the string
and return the final string.

Rolling means increasing the ASCII value of a character by one, wrapping
around: rolling 'z' gives 'a', rolling 'b' gives 'c', etc.

Example 1:
    Input:  s = "bca", roll = [1, 2, 3]
    Output: "eeb"
    Explanation: roll[0] = 1 rolls the first character    -> "cca"
                 roll[1] = 2 rolls the first 2 characters -> "dda"
                 roll[2] = 3 rolls the first 3 characters -> "eeb"

Example 2:
    Input:  s = "zcza", roll = [1, 1, 3, 4]
    Output: "debb"

Constraints:
    - 1 <= len(s) <= 10^5
    - 1 <= roll[i] <= len(s)
    - s consists of lowercase English letters

Expected Complexity:
    - Time: O(n)
    - Auxiliary Space: O(n)
"""
from typing import List
class Solution:
    def findRollOut(self, s: str, roll: List[int], n):
        n = len(s)
        prefix = [0 for _ in range(n)]
        for r in roll:
            prefix[0]+=1
            if r <= n-1:
                prefix[r]-=1
        for i in range(1,n):
            prefix[i]+=prefix[i-1]
        chars = list(s)
        for i in range(n):
            chars[i] = chr((ord(chars[i]) - ord('a') + prefix[i]) % 26 + ord('a'))
        return "".join(chars)
