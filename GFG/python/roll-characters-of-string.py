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
class Solution:
    def findRollOut(self, s, roll, n):
        pass
